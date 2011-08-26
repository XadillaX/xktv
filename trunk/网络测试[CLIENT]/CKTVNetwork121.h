//////////////////////////////////////////////////////////////////////////
//
//	KTV一对一网络类
//
//	Program by 死月(XadillaX) (admin@xcoder.in)
//  Create Date: 2011/08/26
//
//////////////////////////////////////////////////////////////////////////
#ifndef CKTVNETWORK121_H
#define CKTVNETWORK121_H

#pragma once
#include <zmq.hpp>
#include <string>
using namespace std;

#define MAGIC_NUM                   (int)("Xadi")
typedef void                        (*ON_RECEIVE_FUNC)(int, int, const char*, size_t);

struct CKTVNetworkHeader
{
    int                             MagiNum;
    int                             MainID;
    int                             SubID;
    size_t                          Size;
};

class CKTVNetwork121
{
friend DWORD WINAPI ReceiveThread(LPVOID lpParam);

public:
    CKTVNetwork121(const char* szServer, const char* szClient, ON_RECEIVE_FUNC func = NULL);
    virtual ~CKTVNetwork121(void);

    void                            SendMsg(int MainID, int SubID, const char* pData, size_t size);

private:
    zmq::context_t                  m_CtxServer;
    zmq::socket_t                   m_SktServer;

    zmq::context_t                  m_CtxClient;
    zmq::socket_t                   m_SktClient;

    HANDLE                          m_hReceiveThread;
    ON_RECEIVE_FUNC                 m_pReceiveFunc;

    bool                            m_bConnected;
    string                          m_szConnAddr;
};

#endif