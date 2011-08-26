/** 因为连接量不大，所以一个客户端一个线程，没用IOCP，因为只是课程设计的演示，所以也不加密了 */
#ifndef XSIMPLESERVER_H
#define XSIMPLESERVER_H
#include "../../clsocket/PassiveSocket.h"
#include <vector>
#include <string>
#include "xnetworkcommand.h"
#include <map>
using namespace std;

typedef void                                (*ON_ACCEPT_FUNC)(CActiveSocket*);
typedef void                                (*ON_RECEIVE_FUNC)(CActiveSocket*, int, int, void*, size_t);    ///< Socket, MainID, SubID, Data, size

class XSimpleServer
{
friend DWORD WINAPI AcceptThread(LPVOID lpParam);
friend DWORD WINAPI ReceiveThread(LPVOID lpParam);

public:
    XSimpleServer(string address, int port);
    ~XSimpleServer();

    bool                                    StartService();
    bool                                    EndService();
    bool                                    CloseClient(CActiveSocket* pClient);

    bool                                    SendMsg(CActiveSocket* pClient, int MainID, int SubID, void* pData, size_t size);
    bool                                    IsRunning() { return m_bStarted; }

    CRITICAL_SECTION*                       GetCriticalSection() { return &m_CriticalSection; }
    CPassiveSocket*                         GetServerSocket();
    void                                    AddClient(CActiveSocket* pClient);

    bool                                    SetOnAccept(ON_ACCEPT_FUNC func);
    bool                                    SetOnReceive(ON_RECEIVE_FUNC func);

private:
    CPassiveSocket                          m_Socket;
    vector<pair<CActiveSocket*, HANDLE>>    m_pClient;
    map<CActiveSocket*, bool>               m_bExist;

    string                                  m_szAddress;
    int                                     m_nPort;

    bool                                    m_bStarted;

    CRITICAL_SECTION                        m_CriticalSection;

    HANDLE                                  m_hAcceptThread;
    //HANDLE                                  

    ON_ACCEPT_FUNC                          m_pOnAccept;
    ON_RECEIVE_FUNC                         m_pOnReceive;
};

#endif
