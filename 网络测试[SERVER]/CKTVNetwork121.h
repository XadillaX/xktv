//////////////////////////////////////////////////////////////////////////
//
//	KTVһ��һ������
//
//	Program by ����(XadillaX) (admin@xcoder.in)
//  Create Date: 2011/08/26
//
//////////////////////////////////////////////////////////////////////////
#ifndef CKTVNETWORK121_H
#define CKTVNETWORK121_H

#pragma once
#include <zmq.hpp>
#include <string>
#include <queue>
using namespace std;

#define MAGIC_NUM                   (DWORD)(0x49444158)
typedef void                        (*ON_RECEIVE_FUNC)(int, int, char*, size_t);

struct CKTVNetworkHeader
{
    DWORD                           MagiNum;
    int                             MainID;
    int                             SubID;
    size_t                          Size;
};

class CKTVNetwork121
{
friend DWORD WINAPI SendThread(LPVOID lpParam);
friend DWORD WINAPI ReceiveThread(LPVOID lpParam);

public:
    CKTVNetwork121(const char* szServer, const char* szClient, ON_RECEIVE_FUNC func = NULL);
    virtual ~CKTVNetwork121(void);

    void                            SendMsg(int MainID, int SubID, const char* pData, size_t size);

private:
    zmq::context_t                  m_CtxServer;
    zmq::socket_t*                  m_pSktServer;

    HANDLE                          m_hReceiveThread;

    bool                            m_bConnected;
    string                          m_szConnAddr;
};

#endif