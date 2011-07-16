//////////////////////////////////////////////////////////////////////////
//
//    客户端通信类[移植自网狐棋牌]
//
//    Program by 死月(XadillaX) (admin@xcoder.in)
//
//////////////////////////////////////////////////////////////////////////
#ifndef _NETCLIENT_H_
#define _NETCLIENT_H_
#pragma once

#define SERVERPORT 10012
#define BUFFER_SIZE_DEFINE 2048

#include <winsock2.h>
#include <queue>
using namespace std;
#pragma comment(lib,"ws2_32.lib")
#pragma once

/**
 * @brief 消息结点
 */
typedef struct _MSG_NODE
{
    unsigned long DataLength;
    char pData[BUFFER_SIZE_DEFINE];
}MSG_NODE, *PMSG_NODE;

/** 错误定义:套接字上的数据操作正忙 */
#define  CLIENT_FUNERROR 0x100

/**
 * @brief: TCP winsock连接类
 */
class CClientSocket
{
    friend class CNetClient;

public:
    CClientSocket();
    CClientSocket(bool& bSuccess, int iSockType, char* szSvrAddr, unsigned short iSvrPort)
    {
        bSuccess = false;
        bSuccess = CreateSocket(iSockType);
        bSuccess = ConnectSocket(szSvrAddr, iSvrPort);
    }
    virtual ~CClientSocket();

public:
    /** 释放资源 */
    void UnInit();

    /** winsocket处理 */
    bool                CreateSocket(int iSockType) { return CreateSocket(&m_Socket,iSockType); }
    bool                BindSocket(char* szHostAddr, unsigned short iHostPort) { return BindSocket(m_Socket, szHostAddr, iHostPort); }
    bool                ShutDownSocket() { return ShutDownSocket(m_Socket); }
    bool                CloseSocekt(){ return CloseSocket(m_Socket); }
    bool                ConnectSocket(char* szDestAddr, unsigned short iDestPort);

    /**
     * @brief 发送数据
     * @param data 数据指针
     * @param len 数据长度
     * @param retlen 处理长度
     * @param time 等待时间
     * 
     * @return true为成功，否则为失败
     */
    bool                SendMsg(char* data, DWORD len, DWORD* retlen, DWORD time);

    /**
     * @brief 接收数据
     * @param data 数据指针
     * @param len 数据长度
     * @param retlen 处理长度
     * @param time 等待时间
     * 
     * @return true为成功，否则为失败
     */
    bool                RecvMsg(char* data, DWORD len, DWORD* retlen, DWORD time);

    char                m_szDestAddr[255];
    BOOL                m_bEnData;

protected:
    bool                CreateSocket(SOCKET* pNewSocket, int iSockType);
    bool                BindSocket(SOCKET BindSocket, char* szHostAddr, unsigned short iHostPort);
    bool                ShutDownSocket(SOCKET nowSocket);
    bool                CloseSocket(SOCKET nowSocket);
    bool                SendDataS(SOCKET socket, char* data, DWORD len, DWORD* retlen, WSAEVENT hSendEvent, DWORD time);
    bool                RecvDataS(SOCKET socket, char* data, DWORD len, DWORD* retlen, WSAEVENT hRecvEvent, DWORD time);

private:
    bool                SendData(SOCKET socket, char* data, DWORD len, DWORD* retlen, WSAEVENT hSendEvent, DWORD time);
    bool                RecvData(SOCKET socket, char* data, DWORD len, DWORD* retlen, WSAEVENT hRecvEvent, DWORD time);

private:
    SOCKET              m_Socket;
    WSAEVENT            m_hExitEvent;
    struct sockaddr_in  inAddr;
};

/** 通过回调函数调用上层处理函数 */
typedef void __stdcall ProcessRecvClientData(char* pData, unsigned long DataLength, void* pContext);

/** 内部采用标准三线程模型 */
DWORD _stdcall SendProc(LPVOID pParam);
DWORD _stdcall WorkProc(LPVOID pParam);
DWORD _stdcall RecvProc(LPVOID pParam);

/** 网络客户端类 */
class CNetClient  
{
public:
    CNetClient();
    virtual ~CNetClient();

public:
    /**
     * @brief 初始化
     * pProcessRecvClientData 接收数据回调函数
     * pProcessRecvContext 接收数据回调函数上下文
     * szSvrAddr 连接地址
     * iSvrPort 连接端口
     */
    bool Init(ProcessRecvClientData* pProcessRecvClientData, 
        void *pProcessRecvContext,
        LPCTSTR szSvrAddr,
        unsigned long iSvrPort=SERVERPORT,
        BOOL bEnData = TRUE
    );

    /** 清除跟释放资源 */
    void                UnInit(BOOL bWait = FALSE);

    /** 发送数据 */
    bool                SendMsg(char* pData, unsigned long DataLength);

    /** 返回本地地址 */
    LPCTSTR             GetLocalIP() { return IsStart ? HostIpAddr : NULL; }

    bool                IsStarted() { return IsStart; }

protected:
    int InitNetWork(LPCTSTR szSvrAddr,
        unsigned int SvrPort = SERVERPORT,
        LPCTSTR HostIpAddr = NULL
    );

    void                WriteLogString(LPCTSTR strLog);

    CClientSocket       m_sClient;
    ProcessRecvClientData* m_pProcessRecvClientData;
    void*               m_pProcessRecvContext;
    queue<MSG_NODE>     SendMsgQueue;
    CRITICAL_SECTION    SendMsgQueSection;
    HANDLE              hSendEvent;
    queue<MSG_NODE>     RecvMsgQueue;
    CRITICAL_SECTION    RecvMsgQueSection;

    /** 开始工作事件 */
    HANDLE              hWorkEvent;
    /** 退出事件 */
    HANDLE              hExitEvent;

    /** 是否用户进行了反初始化操作，如果是：接收线程将不再调用回调函数 */
    bool                bOprUnInit;

    /** 是否已经被驱动 */
    bool                IsStart;

    TCHAR               HostIpAddr[16];

    BOOL                m_bEnData;

    /** 线程资源 */
    HANDLE              RecvHan;
    HANDLE              WorkHan;
    HANDLE              ThreHan;
    static DWORD WINAPI SendProc(LPVOID pParam);
    static DWORD WINAPI WorkProc(LPVOID pParam);
    static DWORD WINAPI RecvProc(LPVOID pParam);
    void                OnSendProc();
    void                OnWorkProc();
    void                OnRecvProc();
};
#endif

