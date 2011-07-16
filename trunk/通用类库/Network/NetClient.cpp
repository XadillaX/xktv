//////////////////////////////////////////////////////////////////////////
//
//    客户端通信类[移植自网狐棋牌]
//
//    Program by 死月(XadillaX) (admin@xcoder.in)
//
//////////////////////////////////////////////////////////////////////////
#include <atlbase.h>
#include "Network/NetClient.h"
#include <fstream>
using namespace std;

CNetClient::CNetClient()
{
    IsStart = false;
    bOprUnInit = false;
    m_pProcessRecvClientData = NULL;
    m_pProcessRecvContext = NULL;
    WorkHan = NULL;
    RecvHan = NULL;
    ThreHan = NULL;
    hSendEvent = CreateEvent(NULL, false, false, NULL);
    hWorkEvent = CreateEvent(NULL, false, false, NULL);
    hExitEvent = CreateEvent(NULL, false, false, NULL);
}

CNetClient::~CNetClient()
{
    CloseHandle(hSendEvent);
    CloseHandle(hWorkEvent);
    CloseHandle(hExitEvent);
}

DWORD CNetClient::SendProc(LPVOID pParam)
{
    reinterpret_cast<CNetClient*>(pParam)->OnSendProc();
    return 0;
}

void CNetClient::OnSendProc()
{
    CNetClient* pNetClient = (CNetClient*)this;
    HANDLE event[2];
    event[0] = pNetClient->hSendEvent;
    event[1] = pNetClient->hExitEvent;

    while(true)
    {
        Sleep(10);
        EnterCriticalSection(&pNetClient->SendMsgQueSection);\

        /** 队列为空，等待发送事件触发 */
        if(pNetClient->SendMsgQueue.empty())
        {
            LeaveCriticalSection(&pNetClient->SendMsgQueSection);

            /** 为空，或者发送完毕 */
            ResetEvent(pNetClient->hSendEvent);
    
            /** SendProc等待中 */
            DWORD Index = WaitForMultipleObjects(2, event, false, 50);
            if((Index - WAIT_OBJECT_0) == WAIT_TIMEOUT)
            {
                if(pNetClient->bOprUnInit)
                {
                    return;             ///< 应用程序请求退出
                }
            }
            else
            if((Index - WAIT_OBJECT_0) == 1)
            {
                return;
            }
        }
        else
        {
            /** 取下一个结点，并发送 */
            MSG_NODE p = pNetClient->SendMsgQueue.front();
            pNetClient->SendMsgQueue.pop();

            /** 释放队列 */
            LeaveCriticalSection(&pNetClient->SendMsgQueSection);

            DWORD retlen;
            bool bRet = pNetClient->m_sClient.SendMsg(p.pData, p.DataLength, &retlen, WSA_INFINITE);
            if(bRet == false || retlen != p.DataLength)
            {
                if(GetLastError() != CLIENT_FUNERROR)
                pNetClient->m_pProcessRecvClientData(NULL, 0, pNetClient->m_pProcessRecvContext);
                //pNetClient->UnInit();
            }    
        }
    }

    return;
}

DWORD CNetClient::WorkProc(LPVOID pParam)
{
    reinterpret_cast<CNetClient*>(pParam)->OnWorkProc();
    return 0;
}

void CNetClient::OnWorkProc()
{
    CNetClient* pNetClient=(CNetClient*)this;
    HANDLE event[2];
    event[0]=pNetClient->hWorkEvent;
    event[1]=pNetClient->hExitEvent;
    
    while(true)
    {
        Sleep(1);
        EnterCriticalSection(&pNetClient->RecvMsgQueSection);

        /** 队列为空，等待发送事件触发 */
        if(pNetClient->RecvMsgQueue.empty())
        {
            LeaveCriticalSection(&pNetClient->RecvMsgQueSection);

            /** 为空，或者发送完毕 */
            ResetEvent(pNetClient->hWorkEvent);
            
            /** WorkProc正在等待 */
            DWORD Index = WaitForMultipleObjects(2, event, false, 100);
            if((Index - WAIT_OBJECT_0) == WAIT_TIMEOUT)
            {
                if(pNetClient->bOprUnInit)
                {
                    return;             ///< 应用程序请求退出    
                }
            }
            else
            if((Index - WAIT_OBJECT_0) == 1)
            {
                return;
            }
        }
        else
        {
            /** 取下一个结点，并发送 */
            MSG_NODE p = pNetClient->RecvMsgQueue.front();
            pNetClient->RecvMsgQueue.pop();
            
            /** 释放队列 */
            LeaveCriticalSection(&pNetClient->RecvMsgQueSection);
            
            /** 调用回调函数，处理数据 */
            if(m_bEnData)
            {
                char outData[4096];
                long outLen = 4096;
                //CXOREncrypt::CrevasseData(p.pData, outData, outLen);
                pNetClient->m_pProcessRecvClientData(p.pData, p.DataLength, pNetClient->m_pProcessRecvContext);
            }
            else
            {
                pNetClient->m_pProcessRecvClientData(p.pData, p.DataLength, pNetClient->m_pProcessRecvContext);
            }
        }
    }

    return;
}

DWORD CNetClient::RecvProc(LPVOID pParam)
{
    try
    {
        reinterpret_cast<CNetClient*>(pParam)->OnRecvProc();
    }
    catch (...) {
    }

    return 0;
}

void CNetClient::OnRecvProc()
{
    char RecvBuf[BUFFER_SIZE_DEFINE];
    DWORD retlen;
    while(true)
    {
        //Sleep(1);
        //TRACE("\nTheRecvThread Is Waiting...");
        if(!m_sClient.RecvMsg(RecvBuf, BUFFER_SIZE_DEFINE, &retlen, WSA_INFINITE) 
            && GetLastError()!=CLIENT_FUNERROR)
        {
            if(bOprUnInit)
            {
                return;             ///< 应用程序请求退出    
            }

            /** 连接已经被断开，通知上层(通过调用回调函数) */
            m_pProcessRecvClientData(NULL,0, m_pProcessRecvContext);
            //pNetClient->UnInit();
            return ;
        }
        else
        {
            if(bOprUnInit)
            {
                return;             ///< 应用程序请求退出    
            }
    
            /** 没收到字节？还是出错 */
            if(retlen==0 || retlen > BUFFER_SIZE_DEFINE)
            {
                m_pProcessRecvClientData(NULL, 0, m_pProcessRecvContext);
                //pNetClient->UnInit();
                return;
            }

            /** 将接收到的数据放到接收队列里 */
            MSG_NODE Msg;
            Msg.DataLength=retlen;
            memcpy(Msg.pData, RecvBuf, retlen);

            /** 插入消息队列 */
            EnterCriticalSection(&RecvMsgQueSection);
            if(RecvMsgQueue.empty())
            {
                RecvMsgQueue.push(Msg);
                LeaveCriticalSection(&RecvMsgQueSection);
                
                /** 如果消息队列为空，告诉工作线程可以进行工作了 */
                SetEvent(hWorkEvent);
            }
            else
            {
                if(RecvMsgQueue.size() > 50)
                {
                    if(!m_bEnData)
                        while(!RecvMsgQueue.empty()) RecvMsgQueue.pop();
                }
                RecvMsgQueue.push(Msg);

                LeaveCriticalSection(&RecvMsgQueSection);
            }
        }
    }

    return;
}

bool CNetClient::Init(ProcessRecvClientData* pProcessRecvClientData, 
    void *pProcessRecvContext,
    LPCTSTR szSvrAddr,
    unsigned long iSvrPort,
    BOOL bEnData
)
{
    if(pProcessRecvClientData==NULL             /** 回调函数空 */
        || szSvrAddr==NULL                      /** 地址空 */
        || IsStart                              /** 已经启动过了 */
    )
    {
        return false;    
    }

    m_bEnData = bEnData;
    m_sClient.m_bEnData = bEnData;

    InitializeCriticalSection(&SendMsgQueSection);
    InitializeCriticalSection(&RecvMsgQueSection);
    ResetEvent(hExitEvent);
    IsStart = false;
    bOprUnInit = false;
    m_pProcessRecvClientData = pProcessRecvClientData;
    m_pProcessRecvContext = pProcessRecvContext;
    int bRet = InitNetWork(szSvrAddr, iSvrPort, HostIpAddr);
    
    if(0 == bRet)
    {
        IsStart = true;
        return true;
    }
    else
    {
        m_sClient.UnInit();    
        DeleteCriticalSection(&SendMsgQueSection);
        DeleteCriticalSection(&RecvMsgQueSection);    
        
        return false;
    }

}

void CNetClient::UnInit(BOOL bWait)
{
    if(!IsStart) return;

    IsStart = false;
    bOprUnInit = true;
    if(hExitEvent) SetEvent(hExitEvent);
    if(m_sClient.m_hExitEvent) WSASetEvent(m_sClient.m_hExitEvent);

    if(RecvHan)
    {
        /*
        if(bWait)
        {
            bool bloop = true;
            while(bloop)
            {
                if(WaitForSingleObject(RecvHan, 1500) == WAIT_TIMEOUT)
                {
                    if(RecvHan == NULL)
                        bloop =false;
                }
                else
                {
                    bloop =false;
                }
            }
    
        }
        else
        {
            if(WaitForSingleObject(RecvHan, bWait ? INFINITE : 1500) == WAIT_TIMEOUT)
            {
                TerminateThread(RecvHan, -2);
            }
        }*/
        if(WaitForSingleObject(RecvHan,3000) == WAIT_TIMEOUT)
        {
            TerminateThread(RecvHan, -2);
        }

        CloseHandle(RecvHan);
        RecvHan = NULL;
    }

    if(WorkHan)
    {
        /*
        if(bWait)
        {
            bool bloop = true;
            while(bloop)
            {
                if(WaitForSingleObject(WorkHan, 1500) == WAIT_TIMEOUT)
                {
                    if(WorkHan == NULL)
                        bloop =false;
                }
                else
                {
                    bloop =false;
                }
            }
        }
        else
        {
            if(WaitForSingleObject(WorkHan, bWait ? INFINITE : 1500) == WAIT_TIMEOUT)
                TerminateThread(WorkHan, -2);
        }*/
        if(WaitForSingleObject(WorkHan,3000) == WAIT_TIMEOUT)
        {
            TerminateThread(WorkHan, -2);
        }

        CloseHandle(WorkHan);
        WorkHan = NULL;
    }
    if(ThreHan)
    {
        /*
        if(bWait)
        {
            bool bloop = true;
            while(bloop)
            {
                if(WaitForSingleObject(ThreHan, 1500) == WAIT_TIMEOUT)
                {
                    if(ThreHan == NULL)
                        bloop =false;
                }
                else
                {
                    bloop =false;
                }
            }
        }
        else
        {
            if(WaitForSingleObject(ThreHan, bWait ? INFINITE : 1500) == WAIT_TIMEOUT)
                TerminateThread(ThreHan, -2);
        }*/
        if(WaitForSingleObject(ThreHan,3000) == WAIT_TIMEOUT)
        {
            TerminateThread(ThreHan, -2);
        }

        CloseHandle(ThreHan);
        ThreHan = NULL;
    }

    m_sClient.UnInit();    
    
    DeleteCriticalSection(&SendMsgQueSection);
    DeleteCriticalSection(&RecvMsgQueSection);
    
    while(!SendMsgQueue.empty()) SendMsgQueue.pop();
    while(!RecvMsgQueue.empty()) RecvMsgQueue.pop();    
    
    m_pProcessRecvClientData = NULL;
    m_pProcessRecvContext = NULL;
}

int CNetClient::InitNetWork(LPCTSTR szSvrAddr, unsigned int SvrPort, LPCTSTR pHostIpAddress)
{
    int Error = 0;
    WSADATA wsaData;
    memset((void *)pHostIpAddress, 0, sizeof(pHostIpAddress));

    /** Net Start Up */
    char Name[100];
    hostent* pHostEntry;
    in_addr rAddr;
    Error = WSAStartup(MAKEWORD(0x02, 0x02), &wsaData);

    if(Error != 0)
    {
        Error = WSAGetLastError();
        //LogStr.Format("WSAStartUp Faild With Error: %d",Error);
        //WriteLogString(LogStr);

        return Error;
    }

    /** Make Version */
    if(LOBYTE(wsaData.wVersion) != 2 ||
        HIBYTE(wsaData.wVersion) != 2 
    )
    {
        WSACleanup();
        //WriteLogString("The Local Net Version Is not 2");

        return -1;
    }

    /** Get Host Ip */
    Error = gethostname(Name, sizeof(Name));

    if(0 == Error)
    {
        pHostEntry = gethostbyname(Name);

        if(pHostEntry != NULL)
        {
            memcpy(&rAddr, pHostEntry->h_addr_list[0], sizeof(struct in_addr));
            sprintf((char * )pHostIpAddress, "%s", inet_ntoa(rAddr));
        }
        else
        {
            Error = WSAGetLastError();
            //LogStr.Format("GetHostIp faild with Error: %d",Error);
            //WriteLogString(LogStr);
        }
    }
    else
    {
        Error = WSAGetLastError();
        //LogStr.Format("gethostname faild with Error: %d",Error);
        //WriteLogString(LogStr);
    }

    /** Socket Create */
    if(0 == Error)
    {
        if(!m_sClient.CreateSocket(SOCK_STREAM))
        {
            Error = WSAGetLastError();
            //LogStr.Format("Create Client Socket Faild :%d",Error);
            ////WriteLogString(LogStr);
            return Error;
        }
    }

    if(0 == Error)
    {
        //fix me
        USES_CONVERSION;
        if(!m_sClient.ConnectSocket((char*)(szSvrAddr), SvrPort))
        {
            Error=WSAGetLastError();
            //LogStr.Format("Create Client Socket Faild :%d",Error);
            //WriteLogString(LogStr);
            return -1;
        }
    }
    
    /** 启动工作线程，并升高工作线程的等级至最高 */
    if(0 == Error)
    {
        unsigned long WorkID;
        if((WorkHan = CreateThread(NULL, 0, WorkProc, this, 0, &WorkID)) == NULL)
        {
            Error = GetLastError();
            //LogStr.Format("Create WorkThread Faild With Error %d",Error);
            //WriteLogString(LogStr);
            return Error;
        }

        SetThreadPriority(WorkHan, THREAD_PRIORITY_HIGHEST);
    }

    /** 启动接收线程 */
    if(0 == Error)
    {
        unsigned long RecvID;
        if((RecvHan = CreateThread(NULL, 0, RecvProc, this, 0, &RecvID)) == NULL)
        {
            Error = GetLastError();
            //LogStr.Format("Create RecvThread Faild With Error %d",Error);
            //WriteLogString(LogStr);
            SetEvent(hExitEvent);                       ///< 退出先前创建的线程
            return Error;
        }
    }

    /** 启动发送线程 */
    if(0 == Error)
    {
        unsigned long ThrID;
        if((ThreHan = CreateThread(NULL, 0, SendProc, this, 0, &ThrID)) == NULL)
        {
            Error = GetLastError();
            //LogStr.Format("Create SEND Thred Faild With Error %d",Error);
            //WriteLogString(LogStr);
            SetEvent(hExitEvent);                       ///< 退出先前创建的线程
            return Error;
        }
    }

    return Error;
}

bool CNetClient::SendMsg(char* pData, unsigned long DataLength)
{        
    /** 未调用初始化函数 */
    if(!IsStart || pData == NULL || DataLength == 0)return false;

    /** 构造消息 */
    MSG_NODE Msg;
    Msg.DataLength = DataLength;
    memcpy(Msg.pData, pData, DataLength);

    /** 插入消息队列 */
    EnterCriticalSection(&SendMsgQueSection);
    if(SendMsgQueue.empty())
    {
        SendMsgQueue.push(Msg);
        LeaveCriticalSection(&SendMsgQueSection);
        
        /** 如果消息队列为空，告诉等待的发送线程可以发送了 */
        SetEvent(hSendEvent);
    }
    else
    {
        SendMsgQueue.push(Msg);
        LeaveCriticalSection(&SendMsgQueSection);
    }

    return true;
}

void CNetClient::WriteLogString(LPCTSTR strLog)
{
    return;    
}

/*************************************************************************/
CClientSocket::CClientSocket()
{
    inAddr.sin_addr.s_addr = INADDR_NONE;
    m_hExitEvent = NULL;
    m_Socket = 0;
    m_szDestAddr[0] = '\0';    
}            
CClientSocket::~CClientSocket()
{
    if(m_hExitEvent != NULL) WSACloseEvent(m_hExitEvent);
}
void CClientSocket::UnInit()
{
    if(m_hExitEvent != NULL) WSACloseEvent(m_hExitEvent);
    ShutDownSocket();
    CloseSocekt();
    m_szDestAddr[0] = '\0';    
    m_Socket = 0;
    m_hExitEvent = 0;
    //    if(m_hExitEvent != (WSAEVENT)0xcccccccc)WSACloseEvent(m_hExitEvent);
}

bool CClientSocket::CreateSocket(SOCKET* pNewSocket, int iSockType)
{
    if(m_hExitEvent != NULL) WSACloseEvent(m_hExitEvent);
    m_hExitEvent = WSACreateEvent();
    WSAResetEvent(m_hExitEvent);
    
    bool bok = ((*pNewSocket = WSASocket(AF_INET, iSockType, 0, NULL, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET) ? false : true;
    
    if(bok)
    {
        int nrcvbuf = 1024*68; 
        int err = setsockopt(*pNewSocket, SOL_SOCKET, SO_RCVBUF, (char*)&nrcvbuf, sizeof(nrcvbuf));
        err=setsockopt(*pNewSocket, SOL_SOCKET, SO_SNDBUF, (char*)&nrcvbuf, sizeof(nrcvbuf));

        int TimeOut=10000;              ///< 设置发送超时6秒
        if(setsockopt(*pNewSocket, SOL_SOCKET, SO_SNDTIMEO, (char *)&TimeOut, sizeof(TimeOut)) == SOCKET_ERROR)
        {
            return 0;
        }

        TimeOut = 10000;                ///< 设置接收超时6秒
        if(setsockopt(*pNewSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&TimeOut, sizeof(TimeOut)) == SOCKET_ERROR)
        {
            return 0;
        }
    }

    return bok;
}

bool CClientSocket::BindSocket(SOCKET BindSocket, char *szHostAddr, unsigned short iHostPort)
{
    struct sockaddr_in inAddr;
    inAddr.sin_addr.S_un.S_addr = inet_addr(szHostAddr);
    inAddr.sin_family = AF_INET;
    inAddr.sin_port = htons(iHostPort);
    return (bind(BindSocket, (PSOCKADDR)&inAddr, sizeof(inAddr))) == SOCKET_ERROR ? false : true;
}

bool CClientSocket::ShutDownSocket(SOCKET nowSocket)
{
    if(nowSocket)
        return shutdown(nowSocket,SD_BOTH) ? false : true;

    return true;
}

bool CClientSocket::CloseSocket(SOCKET nowSocket)
{
    bool bok = false;
    if(nowSocket)
        bok = (closesocket(nowSocket) == SOCKET_ERROR) ? false : true;

    m_Socket = 0;
    return bok;
}

bool CClientSocket::SendData(SOCKET socket, char* data, DWORD len, DWORD* retlen, WSAEVENT hSendEvent, DWORD time)
{
    if((int)len <= 0 || len > 4096) return true;
    WSABUF DataBuf;
    WSAEVENT hEvents[2];
    WSAOVERLAPPED SendOverLapp;
    DWORD flag;
    char outData[4096];
    long outLen = 4096;

    if(m_bEnData)
    {
        //CXOREncrypt::EncryptData(data, outData, outLen);
        DataBuf.buf = data;
        DataBuf.len = len;
    }
    else
    {
        DataBuf.buf = data;
        DataBuf.len = len;
    }

    hEvents[0] = m_hExitEvent;
    hEvents[1] = hSendEvent;
    memset(&SendOverLapp, 0, sizeof(WSAOVERLAPPED));
    SendOverLapp.hEvent = hSendEvent;
    flag = 0;
    /////////////////////////////////////
    //Godzilar
    int ret;
    
    if((ret = WSASend(socket, &DataBuf, 1, retlen, flag, &SendOverLapp, NULL)) == 0)
    {
        *retlen = len;
        return true;
    }

    else if((ret == SOCKET_ERROR) && (WSAGetLastError() == WSA_IO_PENDING))
    {
        DWORD EventCaused = WSAWaitForMultipleEvents(2, hEvents, FALSE, time, FALSE);
        WSAResetEvent(hSendEvent);

        if(EventCaused == WSA_WAIT_FAILED || EventCaused == WAIT_OBJECT_0)
        {
            if(EventCaused == WAIT_OBJECT_0)
                SetLastError(CLIENT_FUNERROR);
        
            return false;
        }

        flag = 0;
        return WSAGetOverlappedResult(socket, &SendOverLapp, retlen, false, &flag) ? true : false;
    }
    else return false;
}
bool CClientSocket::RecvData(SOCKET socket, char* data, DWORD len, DWORD* retlen, WSAEVENT hRecvEvent, DWORD time)
{
    WSABUF DataBuf;
    WSAEVENT hEvents[2];
    WSAOVERLAPPED RecvOverLapp;
    DWORD flag;

    hEvents[0] = m_hExitEvent;
    hEvents[1] = hRecvEvent;
    DataBuf.buf = data;
    DataBuf.len = len;
    memset(&RecvOverLapp, 0, sizeof(WSAOVERLAPPED));
    RecvOverLapp.hEvent = hRecvEvent;
    flag = 0;
    /////////////////////////////////////
    
    int ret;
    if((ret = WSARecv(socket, &DataBuf, 1, retlen, &flag, &RecvOverLapp, NULL)) == 0)
    {
        return true;
    }
    else
    if((ret == SOCKET_ERROR) && (WSAGetLastError() == WSA_IO_PENDING))
    { 
        DWORD EventCaused = WSAWaitForMultipleEvents(2, hEvents, false, time, false);
        WSAResetEvent(hRecvEvent);

        if(EventCaused == WSA_WAIT_FAILED || EventCaused == WAIT_OBJECT_0)
        {
            if(EventCaused == WAIT_OBJECT_0) SetLastError(CLIENT_FUNERROR);
            return false;
        }

        flag = 0;
        return WSAGetOverlappedResult(socket, &RecvOverLapp, retlen, false, &flag) ? true : false;
    }
    else return false;
}
bool CClientSocket::SendDataS(SOCKET socket, char* data, DWORD len, DWORD* retlen, WSAEVENT hSendEvent, DWORD time)
{
    DWORD left, idx, thisret;
    left = len;
    idx = 0;
    int oflag = 0;
    while(left > 0)
    {
        if(!SendData(socket, &data[idx], left, &thisret, hSendEvent, time))
        {
            *retlen = 0;
            return false;
        }

        WSAResetEvent(hSendEvent);
        left -= thisret;
        idx += thisret;
        if(thisret == 0)
        {
            oflag++;
            if(oflag > 5) break;
        }
    }

    *retlen = idx;
    return (idx == len) ? true : false;
}

bool CClientSocket::RecvDataS(SOCKET socket, char* data, DWORD len, DWORD* retlen, WSAEVENT hRecvEvent, DWORD time)
{
    DWORD left, idx, thisret;
    left = len;
    idx = 0;
    int oflag = 0;
    while(left > 0)
    {
        if(!RecvData(socket, &data[idx], left, &thisret, hRecvEvent, time))
        {
            *retlen = 0;
            return false;
        }

        WSAResetEvent(hRecvEvent);
        left -= thisret;
        idx += thisret;
        if(thisret == 0)
        {
            oflag++;
            if(oflag > 5) break;
        }
    }

    *retlen = idx;
    return (idx == len) ? true : false;
}

bool CClientSocket::SendMsg(char* data, DWORD len, DWORD* retlen, DWORD time)
{
    WSAEVENT hEvent = WSACreateEvent();
    bool bSend = SendDataS(m_Socket, data, len, retlen, hEvent, time);
    WSACloseEvent(hEvent);

    return bSend;
}

bool CClientSocket::RecvMsg(char* data, DWORD len, DWORD* retlen, DWORD time)
{    
    WSAEVENT hEvent = WSACreateEvent();
    bool Recv = RecvData(m_Socket, data, len, retlen, hEvent, time);
    WSACloseEvent(hEvent);
    return Recv;
}

bool CClientSocket::ConnectSocket(char* szDestAddr, unsigned short iDestPort)
{
    inAddr.sin_family = AF_INET;
    inAddr.sin_port = htons(iDestPort);
    inAddr.sin_addr.S_un.S_addr = inet_addr(szDestAddr);
    if(inAddr.sin_addr.s_addr == INADDR_NONE)
    {
        LPHOSTENT lphost;
        lphost = gethostbyname(szDestAddr);
        if (lphost != NULL) inAddr.sin_addr.s_addr = ((LPIN_ADDR)lphost->h_addr)->s_addr;
        else
        {
            WSASetLastError(WSAEINVAL);
            return FALSE;
        }
    }

    strcpy(m_szDestAddr, szDestAddr);
    
    /** 设置非阻塞方式连接 */
    unsigned long ul = 1;
    int ret = ioctlsocket(m_Socket, FIONBIO, (unsigned long*)&ul);
    if(ret == SOCKET_ERROR) return 0;

    bool bOK = (connect(m_Socket, (PSOCKADDR)&inAddr, sizeof(inAddr))) == SOCKET_ERROR ? false : true;
    if(bOK)
    {
        unsigned long ul1 = 0;
        ret = ioctlsocket(m_Socket, FIONBIO, (unsigned long*)&ul1);
        return bOK;
    }

    /** select 模型，即设置超时 */
    struct timeval timeout;
    fd_set r;

    FD_ZERO(&r);
    FD_SET(m_Socket, &r);
    timeout.tv_sec = 4;             ///< 连接超时15秒
    timeout.tv_usec = 50000;
    ret = select(0, 0, &r, 0, &timeout);
    if ( ret <= 0 )
    {
        bOK = false;
    }
    else bOK = true;

    /** 一般非锁定模式套接比较难控制，可以根据实际情况考虑 再设回阻塞模式 */
    unsigned long ul1 = 0 ;
    ret = ioctlsocket(m_Socket, FIONBIO, (unsigned long*)&ul1);
    if(ret == SOCKET_ERROR)
    {
        bOK = false;
    } 

    return bOK;
}
