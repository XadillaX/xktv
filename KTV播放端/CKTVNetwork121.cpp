#include "CKTVNetwork121.h"

struct _receive_param
{
    zmq::socket_t* socket;
    ON_RECEIVE_FUNC func;
};

struct _send_param
{
    zmq::socket_t* socket;
    CKTVNetworkHeader header;
    char* data;
};

DWORD WINAPI SendThread(LPVOID lpParam)
{
    _send_param* sp = (_send_param*)lpParam;
    char* pData = new char[sp->header.Size + sizeof(CKTVNetworkHeader) + 16];
    memcpy(pData, &sp->header, sizeof(CKTVNetworkHeader));
    memcpy(pData + sizeof(CKTVNetworkHeader), sp->data, sp->header.Size);

    /** 发送 */
    zmq::message_t request(sp->header.Size + sizeof(CKTVNetworkHeader) + 16);
    memcpy(request.data(), pData, sp->header.Size + sizeof(CKTVNetworkHeader));
    sp->socket->send(request);

    delete sp->data;
    delete sp;

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

        Sleep(1);
    }
    delete rp;

    return 0;
}

CKTVNetwork121::CKTVNetwork121(const char* szServer, const char* szClient, ON_RECEIVE_FUNC func) :
    m_CtxServer(1),
    m_CtxClient(1),
    m_SktServer(m_CtxServer, ZMQ_REP),
    m_SktClient(m_CtxClient, ZMQ_REQ)
{
    m_SktServer.bind(szServer);
    m_SktClient.connect(szClient);

    _receive_param* rp = new _receive_param();
    rp->socket = &m_SktServer;
    rp->func = func;
    m_hReceiveThread = ::CreateThread(NULL, 0, ReceiveThread, rp, 0, 0);
}

CKTVNetwork121::~CKTVNetwork121(void)
{
    ::TerminateThread(m_hReceiveThread, 0);
}

void CKTVNetwork121::SendMsg(int MainID, int SubID, char* pData, size_t size)
{
    _send_param* sp = new _send_param();
    sp->header.MagiNum = MAGIC_NUM;
    sp->header.MainID = MainID;
    sp->header.SubID = SubID;
    sp->header.Size = size;

    char* data = new char[size];
    memcpy(data, pData, size);

    sp->data = data;
    sp->socket = &m_SktClient;

    ::CreateThread(NULL, 0, SendThread, sp, 0, 0);
}
