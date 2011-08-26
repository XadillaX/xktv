#include "Network/XSimpleServer.h"

struct __receive_param
{
    XSimpleServer*                      pServer;
    CActiveSocket*                      pClient;
};

DWORD WINAPI ReceiveThread(LPVOID lpParam)
{
    __receive_param* rp = (__receive_param*)lpParam;

    while(rp->pServer->IsRunning())
    {
        if(rp->pServer->m_bExist.find(rp->pClient) == rp->pServer->m_bExist.end() || rp->pServer->m_bExist[rp->pClient])
        {
            break;
        }

        if(rp->pClient->Receive(MAX_PACKAGE_SIZE) != NULL)
        {
            /** �������� */
            char* pData = (char*)rp->pClient->GetData();

            /** ��ȡ����ͷ */
            XNetworkHead Header;
            memcpy(&Header, pData, sizeof(XNetworkHead));
            if(XNETWORK_MAGIC_NUM != Header.MagicNum) continue;

            /** ������� */
            char* pRealData = pData + sizeof(XNetworkHead);

            /** ����Receive���� */
            if(NULL != rp->pServer->m_pOnReceive)
            {
                rp->pServer->m_pOnReceive(rp->pClient, Header.MainID, Header.SubID, pRealData, Header.Size);
            }
        }
    }

    return 0;
}

DWORD WINAPI AcceptThread(LPVOID lpParam)
{
    XSimpleServer* pXSS = (XSimpleServer*)lpParam;

    while(pXSS->IsRunning())
    {
        /** Accept */
        CActiveSocket *pClient = NULL;
        if((pClient = pXSS->GetServerSocket()->Accept()) != NULL)
        {
            /** �½�Socket�߳� */
            __receive_param *param = new __receive_param();
            param->pClient = pClient;
            param->pServer = pXSS;
            pair<CActiveSocket*, HANDLE> CLIENT;
            CLIENT.first = pClient;
            CLIENT.second = ::CreateThread(NULL, 0, ReceiveThread, param, 0, NULL);

            /** ��Socket����vector */
            ::EnterCriticalSection(pXSS->GetCriticalSection());
            pXSS->m_pClient.push_back(CLIENT);
            pXSS->m_bExist[pClient] = true;
            ::LeaveCriticalSection(pXSS->GetCriticalSection());
            
            /** ����Accept���� */
            if(NULL != pXSS->m_pOnAccept)
            {
                pXSS->m_pOnAccept(pClient);
            }
        }

        Sleep(1);
    }

    return 0;
}

/**************************************************************************/
XSimpleServer::XSimpleServer(string address, int port) :
    m_bStarted(false),
    m_pOnAccept(NULL),
    m_pOnReceive(NULL)
{
    m_szAddress = address;
    m_nPort = port;
}

XSimpleServer::~XSimpleServer()
{
    EndService();
}

bool XSimpleServer::StartService()
{
    /** ��ʼ�� */
    if(!m_Socket.Initialize())
    {
        m_bStarted = false;
        return false;
    }

    /** ���� */
    if(!m_Socket.Listen((const uint8*)m_szAddress.c_str(), m_nPort))
    {
        m_bStarted = false;
        return false;
    }

    m_bStarted = true;

    /** Accept�߳� */
    Sleep(1);
    m_hAcceptThread = ::CreateThread(NULL, 0, AcceptThread, this, 0, NULL);
    if(0 == m_hAcceptThread)
    {
        m_bStarted = false;
        false;
    }

    return true;
}

CPassiveSocket* XSimpleServer::GetServerSocket()
{
    return &m_Socket;
}

bool XSimpleServer::SetOnAccept(ON_ACCEPT_FUNC func)
{
    if(m_bStarted) return false;
    else m_pOnAccept = func;

    return true;
}

bool XSimpleServer::SetOnReceive(ON_RECEIVE_FUNC func)
{
    if(m_bStarted) return false;
    else m_pOnReceive = func;

    return true;
}

bool XSimpleServer::SendMsg(CActiveSocket* pClient, int MainID, int SubID, void* pData, size_t size)
{
    /** ��Ϣͷ */
    XNetworkHead Header;
    Header.MagicNum = XNETWORK_MAGIC_NUM;
    Header.MainID = MainID;
    Header.SubID = SubID;
    Header.Size = size;

    /** ������ */
    char pcData[MAX_PACKAGE_SIZE];
    memcpy(pcData, &Header, sizeof(XNetworkHead));
    memcpy(pcData + sizeof(XNetworkHead), pData, size);

    /** ���� */
    return (size + sizeof(XNetworkHead)) == (pClient->Send((const uint8*)pcData, size + sizeof(XNetworkHead)));
}

bool XSimpleServer::EndService()
{
    if(!m_bStarted) return false;

    /** ɾ�����ڸ� */
    for(map<CActiveSocket*, bool>::iterator it = m_bExist.begin(); it != m_bExist.end(); it++)
    {
        it->second = false;
    }

    /** �ر�����socket */
    while(!m_pClient.empty())
    {
        m_pClient[m_pClient.size() - 1].first->Close();
        delete m_pClient[m_pClient.size() - 1].first;
        m_pClient.pop_back();
    }

    m_Socket.Close();

    return true;
}

bool XSimpleServer::CloseClient(CActiveSocket* pClient)
{
    if(m_bExist.find(pClient) == m_bExist.end() || m_bExist[pClient] == false) return false;

    m_bExist[pClient] = false;
    for(vector<pair<CActiveSocket*, HANDLE>>::iterator it = m_pClient.begin(); it != m_pClient.end(); it++)
    {
        if(pClient == (*it).first)
        {
            m_pClient.erase(it);
            break;
        }
    }

    pClient->Close();
    delete pClient;

    return true;
}
