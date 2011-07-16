//////////////////////////////////////////////////////////////////////////
//
//    �ͻ�����[��ֲ����������]
//
//    Program by ����(XadillaX) (admin@xcoder.in)
//
//////////////////////////////////////////////////////////////////////////
#ifndef _ClientNetworkObject_H_
#define _ClientNetworkObject_H_

#pragma once
#include "NetClient.h"
#include <list>
#include <wtypes.h>
#include "NetworkCommand.h"
using namespace std;

struct PACKET_ {
    BYTE*                       pData;
    DWORD                       dwLength;
    time_t                      tm;
    long                        lLive;
};
typedef list<PACKET_>           LIST_PACKET_;
typedef LIST_PACKET_::iterator  LIST_PACKET_IT;

class ClientNetworkObject
{
public:
    ClientNetworkObject(void);
    virtual ~ClientNetworkObject(void);

    BOOL                        Start(LPCTSTR szSvrAddr, unsigned long iSvrPort, BOOL bEnData = TRUE);
    void                        Stop();

    /** send */
    bool                        SendCommand(WORD wMainCmdID, WORD wSubCmdID, void* pData, WORD wDataSize);
    bool                        SendCommand(WORD wMainCmdID, WORD wSubCmdID);
    bool                        SendRawData(BYTE* pData, unsigned long Length);

    /** misc */
    bool    IsConnected();

protected:
    static void __stdcall       ProcessRecvDataFun(char* pData, unsigned long DataLength, void* pContext);
    void __stdcall              OnProcessRecvDataFun(char* pData, unsigned long DataLength);
    
    virtual void                OnProcessRecvData(CMD_Head tagHead, BYTE* pData);

protected:
    CNetClient*                 m_pNetClient;
    bool                        bCmdConnect;

protected:
    /** �������� */
    WORD                        CrevasseBuffer(BYTE cbDataBuffer[], WORD wDataSize);
    /** �������� */
    WORD                        EncryptBuffer(BYTE cbDataBuffer[], WORD wDataSize, WORD wBufferSize);

private:
    /** �ֽ�ӳ�� */
    inline WORD                 SeedRandMap(WORD wSeed);

    /** ����ӳ�� */
    inline BYTE                 MapSendByte(BYTE cbData);

    /** ����ӳ�� */
    inline BYTE                 MapRecvByte(BYTE cbData);

protected:
    BYTE                        m_cbSendRound;                        //�ֽ�ӳ��
    BYTE                        m_cbRecvRound;                        //�ֽ�ӳ��
    DWORD                       m_dwSendXorKey;                       //������Կ
    DWORD                       m_dwRecvXorKey;                       //������Կ

    /** �������� */
protected:
    DWORD                       m_dwSendTickCount;                    //����ʱ��
    DWORD                       m_dwRecvTickCount;                    //����ʱ��
    DWORD                       m_dwSendPacketCount;                  //���ͼ���
    DWORD                       m_dwRecvPacketCount;                  //���ܼ���
};

#endif
