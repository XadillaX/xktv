//////////////////////////////////////////////////////////////////////////
//
//    客户端类[移植自网狐棋牌]
//
//    Program by 死月(XadillaX) (admin@xcoder.in)
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
    /** 解密数据 */
    WORD                        CrevasseBuffer(BYTE cbDataBuffer[], WORD wDataSize);
    /** 加密数据 */
    WORD                        EncryptBuffer(BYTE cbDataBuffer[], WORD wDataSize, WORD wBufferSize);

private:
    /** 字节映射 */
    inline WORD                 SeedRandMap(WORD wSeed);

    /** 发送映射 */
    inline BYTE                 MapSendByte(BYTE cbData);

    /** 接收映射 */
    inline BYTE                 MapRecvByte(BYTE cbData);

protected:
    BYTE                        m_cbSendRound;                        //字节映射
    BYTE                        m_cbRecvRound;                        //字节映射
    DWORD                       m_dwSendXorKey;                       //发送密钥
    DWORD                       m_dwRecvXorKey;                       //接收密钥

    /** 计数变量 */
protected:
    DWORD                       m_dwSendTickCount;                    //发送时间
    DWORD                       m_dwRecvTickCount;                    //接收时间
    DWORD                       m_dwSendPacketCount;                  //发送计数
    DWORD                       m_dwRecvPacketCount;                  //接受计数
};

#endif
