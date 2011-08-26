#include "CKTVNetwork121.h"

struct _receive_param
{
    zmq::socket_t* socket;
    ON_RECEIVE_FUNC func;
};

struct _send_param
{
    CKTVNetworkHeader header;
    char* data;
    char address[128];
};

DWORD WINAPI SendThread(LPVOID lpParam)
{
    _send_param* sp = (_send_param*)lpParam;
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);
    socket.connect(sp->address);

    /** 数据 */
    char* pData = new char[sp->header.Size + sizeof(CKTVNetworkHeader)];
    memcpy(pData, &sp->header, sizeof(CKTVNetworkHeader));
    memcpy(pData + sizeof(CKTVNetworkHeader), sp->data, sp->header.Size);
    zmq::message_t request(sizeof(CKTVNetworkHeader) + sp->header.Size);
    memcpy(request.data(), pData, sizeof(CKTVNetworkHeader) + sp->header.Size);

    socket.send(request);

    zmq::message_t reply;
    socket.recv(&reply);

    delete []pData;
    delete []sp->data;
    socket.close();

    return 0;
}

DWORD WINAPI ReceiveThread(LPVOID lpParam)
{
    _receive_param* rp = (_receive_param*)lpParam;
    while(true)
    {
        /** 接收数据 */
        zmq::message_t request;
        rp->socket->recv(&request);

        /** 分析数据 */
        CKTVNetworkHeader Header;
        char* pData = (char*)request.data();
        memcpy(&Header, pData, sizeof(CKTVNetworkHeader));

        /** 验证 */
        if(MAGIC_NUM != Header.MagiNum) continue;

        /** OnReceive */
        if(NULL != rp->func)
        {
            rp->func(Header.MainID, Header.SubID, pData + sizeof(CKTVNetworkHeader), Header.Size);
        }

        /** 返还数据 */
        zmq::message_t reply(0);
        rp->socket->send(reply);

        Sleep(1);
    }
    delete rp;

    return 0;
}

CKTVNetwork121::CKTVNetwork121(const char* szServer, const char* szClient, ON_RECEIVE_FUNC func) :
    m_CtxServer(1),
    m_hReceiveThread(0)
{
    m_pSktServer = new zmq::socket_t(m_CtxServer, ZMQ_REP);

    m_pSktServer->bind(szServer);
    m_szConnAddr = szClient;

    /** 接受线程 */
    _receive_param* rp = new _receive_param();
    rp->socket = m_pSktServer;
    rp->func = func;

    m_hReceiveThread = ::CreateThread(NULL, 0, ReceiveThread, rp, 0, 0);
}

CKTVNetwork121::~CKTVNetwork121(void)
{
    if(m_hReceiveThread != 0) ::TerminateThread(m_hReceiveThread, 0);

    delete m_pSktServer;
}

void CKTVNetwork121::SendMsg(int MainID, int SubID, const char* pData, size_t size)
{
    /** 准备数据 */
    _send_param* sp = new _send_param();

    /** 数据头 */
    sp->header.MagiNum = MAGIC_NUM;
    sp->header.MainID = MainID;
    sp->header.SubID = SubID;
    sp->header.Size = size;

    /** 数据体 */
    sp->data = new char[size];
    memcpy(sp->data, pData, size);

    /** 地址 */
    strcpy(sp->address, m_szConnAddr.c_str());

    /** 发送线程 */
    ::CreateThread(NULL, 0, SendThread, sp, 0, 0);
}
