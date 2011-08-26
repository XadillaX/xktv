#include "Network/XSimpleServer.h"

DWORD WINAPI AcceptThread(LPVOID lpParam)
{

    return 0;
}

XSimpleServer::XSimpleServer(string address, int port) :
    m_bStarted(false)
{
    m_szAddress = address;
    m_nPort = port;
}

XSimpleServer::~XSimpleServer()
{
}

bool XSimpleServer::StartService()
{
    if(!m_Socket.Initialize()) return false;
    if(!m_Socket.Listen((const uint8*)m_szAddress.c_str(), m_nPort)) return false;

    return true;
}
