/** 因为连接量不大，所以一个客户端一个线程 */
#ifndef XSIMPLESERVER_H
#define XSIMPLESERVER_H
#include <windows.h>
#include <clsocket/PassiveSocket.h>
#include <vector>
#include <string>
using namespace std;

#define MAX_PACKAGE_SIZE                    10240

class XSimpleServer
{
public:
    XSimpleServer(string address, int port);
    ~XSimpleServer();

    bool                                    StartService();

    CRITICAL_SECTION*                       GetCriticalSection() { return m_CriticalSection; }
    CPassiveSocket*                         GetServerSocket();
    void                                    AddClient(CActiveSocket* pClient);

private:
    CPassiveSocket                          m_Socket;
    vector<CActiveSocket*>                  m_pClient;

    string                                  m_szAddress;
    int                                     m_nPort;

    bool                                    m_bStarted;

    CRITICAL_SECTION                        m_CriticalSection;

    HANDLE                                  
};

#endif
