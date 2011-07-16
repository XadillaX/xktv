//////////////////////////////////////////////////////////////////////////
//
//    �ͻ���ͨ����[��ֲ����������]
//
//    Program by ����(XadillaX) (admin@xcoder.in)
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
 * @brief ��Ϣ���
 */
typedef struct _MSG_NODE
{
    unsigned long DataLength;
    char pData[BUFFER_SIZE_DEFINE];
}MSG_NODE, *PMSG_NODE;

/** ������:�׽����ϵ����ݲ�����æ */
#define  CLIENT_FUNERROR 0x100

/**
 * @brief: TCP winsock������
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
    /** �ͷ���Դ */
    void UnInit();

    /** winsocket���� */
    bool                CreateSocket(int iSockType) { return CreateSocket(&m_Socket,iSockType); }
    bool                BindSocket(char* szHostAddr, unsigned short iHostPort) { return BindSocket(m_Socket, szHostAddr, iHostPort); }
    bool                ShutDownSocket() { return ShutDownSocket(m_Socket); }
    bool                CloseSocekt(){ return CloseSocket(m_Socket); }
    bool                ConnectSocket(char* szDestAddr, unsigned short iDestPort);

    /**
     * @brief ��������
     * @param data ����ָ��
     * @param len ���ݳ���
     * @param retlen ������
     * @param time �ȴ�ʱ��
     * 
     * @return trueΪ�ɹ�������Ϊʧ��
     */
    bool                SendMsg(char* data, DWORD len, DWORD* retlen, DWORD time);

    /**
     * @brief ��������
     * @param data ����ָ��
     * @param len ���ݳ���
     * @param retlen ������
     * @param time �ȴ�ʱ��
     * 
     * @return trueΪ�ɹ�������Ϊʧ��
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

/** ͨ���ص����������ϲ㴦���� */
typedef void __stdcall ProcessRecvClientData(char* pData, unsigned long DataLength, void* pContext);

/** �ڲ����ñ�׼���߳�ģ�� */
DWORD _stdcall SendProc(LPVOID pParam);
DWORD _stdcall WorkProc(LPVOID pParam);
DWORD _stdcall RecvProc(LPVOID pParam);

/** ����ͻ����� */
class CNetClient  
{
public:
    CNetClient();
    virtual ~CNetClient();

public:
    /**
     * @brief ��ʼ��
     * pProcessRecvClientData �������ݻص�����
     * pProcessRecvContext �������ݻص�����������
     * szSvrAddr ���ӵ�ַ
     * iSvrPort ���Ӷ˿�
     */
    bool Init(ProcessRecvClientData* pProcessRecvClientData, 
        void *pProcessRecvContext,
        LPCTSTR szSvrAddr,
        unsigned long iSvrPort=SERVERPORT,
        BOOL bEnData = TRUE
    );

    /** ������ͷ���Դ */
    void                UnInit(BOOL bWait = FALSE);

    /** �������� */
    bool                SendMsg(char* pData, unsigned long DataLength);

    /** ���ر��ص�ַ */
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

    /** ��ʼ�����¼� */
    HANDLE              hWorkEvent;
    /** �˳��¼� */
    HANDLE              hExitEvent;

    /** �Ƿ��û������˷���ʼ������������ǣ������߳̽����ٵ��ûص����� */
    bool                bOprUnInit;

    /** �Ƿ��Ѿ������� */
    bool                IsStart;

    TCHAR               HostIpAddr[16];

    BOOL                m_bEnData;

    /** �߳���Դ */
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

