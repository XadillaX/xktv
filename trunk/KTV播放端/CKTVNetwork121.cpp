#include "CKTVNetwork121.h"

struct _receive_param
{
    zmq::socket_t* socket;
    ON_RECEIVE_FUNC func;
};

struct _send_param
{
    zmq::socket_t* socket;
    CRITICAL_SECTION* cs;
    queue<SendData>* queue;
};

DWORD WINAPI SendThread(LPVOID lpParam)
{
    _send_param* sp = (_send_param*)lpParam;
    zmq::socket_t* socket = sp->socket;
    CRITICAL_SECTION* cs = sp->cs;
    queue<SendData>* queue = sp->queue;
    delete sp;

    while(true)
    {
        SendData sd;
        sd.header = NULL;
        sd.data = NULL;

        /** 从队列中获取 */
        ::EnterCriticalSection(cs);
        if(!queue->empty())
        {
            sd = queue->front();
            queue->pop();
        }
        ::LeaveCriticalSection(cs);

        /** 有消息 */
        if(sd.header != NULL && sd.data != NULL)
        {
            try{
                /** 数据 */
                char* pData = new char[sd.header->Size + sizeof(CKTVNetworkHeader)];
                memcpy(pData, sd.header, sizeof(CKTVNetworkHeader));
                memcpy(pData + sizeof(CKTVNetworkHeader), sd.data, sd.header->Size);
                zmq::message_t request(sizeof(CKTVNetworkHeader) + sd.header->Size);
                memcpy(request.data(), pData, sizeof(CKTVNetworkHeader) + sd.header->Size);

                /** 发送 */
                socket->send(request);

                /** 反馈 */
                zmq::message_t reply;
                socket->recv(&reply);

                delete []pData;
                delete []sd.data;
                delete sd.header;
            }
            catch(zmq::error_t e)
            {
                printf("[ERROR 0x%X] %s\n", e.num(), e.what());
            }
        }
        
        Sleep(1);
    }

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
    m_hReceiveThread(0),
    m_hSendThread(0),
    m_pSktClient(NULL),
    m_CtxClient(2)
{
    m_pSktServer = new zmq::socket_t(m_CtxServer, ZMQ_REP);

    m_pSktServer->bind(szServer);
    m_szConnAddr = szClient;

    /** 接受线程 */
    _receive_param* rp = new _receive_param();
    rp->socket = m_pSktServer;
    rp->func = func;

    ::InitializeCriticalSection(&m_CriticalSection);
    m_hReceiveThread = ::CreateThread(NULL, 0, ReceiveThread, rp, 0, 0);
}

CKTVNetwork121::~CKTVNetwork121(void)
{
    if(m_hReceiveThread != 0) ::TerminateThread(m_hReceiveThread, 0);
    if(m_hSendThread != 0) ::TerminateThread(m_hSendThread, 0);

    m_pSktServer->close();
    m_pSktClient->close();
    delete m_pSktServer;
    delete m_pSktClient;
}

void CKTVNetwork121::SendMsg(int MainID, int SubID, const char* pData, size_t size)
{
    if(NULL == m_pSktClient)
    {
        m_pSktClient = new zmq::socket_t(m_CtxClient, ZMQ_REQ);
        m_pSktClient->connect(m_szConnAddr.c_str());

        _send_param* sp = new _send_param();
        sp->cs = &m_CriticalSection;
        sp->queue = &m_SendQueue;
        sp->socket = m_pSktClient;

        m_hSendThread = ::CreateThread(NULL, 0, SendThread, sp, 0, 0);
    }

    /** 准备数据 */
    SendData sd;
    sd.header = new CKTVNetworkHeader();

    /** 数据头 */
    sd.header->MagiNum = MAGIC_NUM;
    sd.header->MainID = MainID;
    sd.header->SubID = SubID;
    sd.header->Size = size;

    /** 数据体 */
    sd.data = new char[size];
    memcpy(sd.data, pData, size);

    /** 加入队列 */
    ::EnterCriticalSection(&m_CriticalSection);
    m_SendQueue.push(sd);
    ::LeaveCriticalSection(&m_CriticalSection);
}
