//////////////////////////////////////////////////////////////////////////
//
//    客户端类[移植自网狐棋牌]
//
//    Program by 死月(XadillaX) (admin@xcoder.in)
//
//////////////////////////////////////////////////////////////////////////
#include "Network/ClientNetworkObject.h"
#include <map>
std::map<DWORD, HANDLE> _hThreadMAP;

extern int MyRand();

ClientNetworkObject::ClientNetworkObject(void)
{
    m_pNetClient = NULL;
    bCmdConnect = false;

    m_cbSendRound = 0;
    m_cbRecvRound = 0;
    m_dwSendXorKey = 0;
    m_dwRecvXorKey = 0;
    m_dwSendTickCount = 0;
    m_dwRecvTickCount = 0;
    m_dwSendPacketCount = 0;
}

ClientNetworkObject::~ClientNetworkObject(void)
{
}

/** 随机映射 */
WORD ClientNetworkObject::SeedRandMap(WORD wSeed)
{
    DWORD dwHold = wSeed;
    return (WORD)((dwHold = dwHold * 241103L + 2533101L) >> 16);
}

/** 映射发送数据 */
BYTE ClientNetworkObject::MapSendByte(BYTE const cbData)
{
    BYTE cbMap = g_SendByteMap[(BYTE)(cbData+m_cbSendRound)];
    m_cbSendRound += 3;
    return cbMap;
}

/** 映射接收数据 */
BYTE ClientNetworkObject::MapRecvByte(BYTE const cbData)
{
    BYTE cbMap = g_RecvByteMap[cbData] - m_cbRecvRound;
    m_cbRecvRound += 3;
    return cbMap;
}

/** 加密数据 */
WORD ClientNetworkObject::EncryptBuffer(BYTE pcbDataBuffer[], WORD wDataSize, WORD wBufferSize)
{
    int i = 0;

    /** 效验参数 */
    if(wDataSize < sizeof(CMD_Head)) return 0;
    if(wBufferSize < (wDataSize + 2 * sizeof(DWORD))) return 0;
    if(wDataSize > (sizeof(CMD_Head) + BUFFER_SIZE_DEFINE)) return 0;

    /** 调整长度 */
    WORD wEncryptSize = wDataSize - sizeof(CMD_Command), wSnapCount = 0;
    if ((wEncryptSize % sizeof(DWORD)) != 0)
    {
        wSnapCount = sizeof(DWORD) - wEncryptSize % sizeof(DWORD);
        memset(pcbDataBuffer + sizeof(CMD_Info) + wEncryptSize, 0, wSnapCount);
    }

    /** 效验码与字节映射 */
    BYTE cbCheckCode = 0;
    for (WORD i = sizeof(CMD_Info); i < wDataSize; i++)
    {
        cbCheckCode += pcbDataBuffer[i];
        pcbDataBuffer[i] = MapSendByte(pcbDataBuffer[i]);
    }

    /** 填写信息头 */
    CMD_Head* pHead = (CMD_Head*)pcbDataBuffer;
    pHead->CmdInfo.cbCheckCode = ~cbCheckCode + 1;
    pHead->CmdInfo.wPacketSize = wDataSize;
    pHead->CmdInfo.cbVersion = SOCKET_VER;

    /** 创建密钥 */
    DWORD dwXorKey = m_dwSendXorKey;
    if (m_dwSendPacketCount == 0)
    {
        /** 生成第一次随机种子 */
        GUID Guid;
        CoCreateGuid(&Guid);
        dwXorKey = GetTickCount() * GetTickCount();
        dwXorKey ^= Guid.Data1;
        dwXorKey ^= Guid.Data2;
        dwXorKey ^= Guid.Data3;
        dwXorKey ^= *((DWORD*)Guid.Data4);

        /** 随机映射种子 */
        dwXorKey = SeedRandMap((WORD)dwXorKey);
        dwXorKey |= ((DWORD)SeedRandMap((WORD)(dwXorKey >> 16))) << 16;
        dwXorKey ^= g_dwPacketKey;
        m_dwSendXorKey = dwXorKey;
        m_dwRecvXorKey = dwXorKey;
    }

    /** 加密数据 */
    WORD* pwSeed = (WORD *)(pcbDataBuffer + sizeof(CMD_Info));
    DWORD* pdwXor = (DWORD *)(pcbDataBuffer + sizeof(CMD_Info));
    WORD wEncrypCount = (wEncryptSize + wSnapCount) / sizeof(DWORD);
    for (WORD i = 0; i < wEncrypCount; i++)
    {
        *pdwXor++ ^= dwXorKey;
        dwXorKey = SeedRandMap(*pwSeed++);
        dwXorKey |= ((DWORD)SeedRandMap(*pwSeed++)) << 16;
        dwXorKey ^= g_dwPacketKey;
    }

    /** 插入密钥 */
    if (m_dwSendPacketCount == 0)
    {
        MoveMemory(pcbDataBuffer + sizeof(CMD_Head) + sizeof(DWORD), pcbDataBuffer + sizeof(CMD_Head), wDataSize);
        *((DWORD *)(pcbDataBuffer + sizeof(CMD_Head))) = m_dwSendXorKey;
        pHead->CmdInfo.wPacketSize += sizeof(DWORD);
        wDataSize += sizeof(DWORD);
    }

    /** 设置变量 */
    m_dwSendPacketCount++;
    m_dwSendXorKey = dwXorKey;

    return wDataSize;
}

/** 解密数据 */
WORD ClientNetworkObject::CrevasseBuffer(BYTE pcbDataBuffer[], WORD wDataSize)
{
    /** 效验参数 */
    if(m_dwSendPacketCount <= 0) return 0;
    if(wDataSize < sizeof(CMD_Head)) return 0;
    if(((CMD_Head*)pcbDataBuffer)->CmdInfo.wPacketSize != wDataSize) return 0;

    /** 调整长度 */
    WORD wSnapCount = 0;
    if ((wDataSize % sizeof(DWORD)) != 0)
    {
        wSnapCount = sizeof(DWORD) - wDataSize % sizeof(DWORD);
        memset(pcbDataBuffer + wDataSize, 0, wSnapCount);
    }

    /** 解密数据 */
    DWORD dwXorKey = m_dwRecvXorKey;
    DWORD* pdwXor = (DWORD *)(pcbDataBuffer + sizeof(CMD_Info));
    WORD* pwSeed = (WORD *)(pcbDataBuffer + sizeof(CMD_Info));
    WORD wEncrypCount = (wDataSize + wSnapCount - sizeof(CMD_Info)) / 4;
    for(WORD i = 0; i < wEncrypCount; i++)
    {
        if((i == (wEncrypCount - 1)) && (wSnapCount > 0))
        {
            BYTE* pcbKey = ((BYTE*) & m_dwRecvXorKey) + sizeof(DWORD) - wSnapCount;
            CopyMemory(pcbDataBuffer + wDataSize, pcbKey, wSnapCount);
        }

        dwXorKey = SeedRandMap(*pwSeed++);
        dwXorKey |= ((DWORD)SeedRandMap(*pwSeed++)) << 16;
        dwXorKey ^= g_dwPacketKey;
        *pdwXor++ ^= m_dwRecvXorKey;
        m_dwRecvXorKey = dwXorKey;
    }

    /** 效验码与字节映射 */
    CMD_Head* pHead = (CMD_Head*)pcbDataBuffer;
    BYTE cbCheckCode = pHead->CmdInfo.cbCheckCode;
    for (int i = sizeof(CMD_Info); i < wDataSize; i++)
    {
        pcbDataBuffer[i] = MapRecvByte(pcbDataBuffer[i]);
        cbCheckCode += pcbDataBuffer[i];
    }
    if (cbCheckCode != 0) throw TEXT("数据包效验码错误");

    return wDataSize;
}

BOOL ClientNetworkObject::Start(LPCTSTR szSvrAddr, unsigned long iSvrPort, BOOL bEnData)
{
    m_cbSendRound = 0;
    m_cbRecvRound = 0;
    m_dwSendXorKey = 0x12345678;
    m_dwRecvXorKey = 0x12345678;
    m_dwSendTickCount = GetTickCount() / 1000L;
    m_dwRecvTickCount = GetTickCount() / 1000L;
    m_dwSendPacketCount = 0;

    m_pNetClient = new CNetClient;
    if(!m_pNetClient->Init(ProcessRecvDataFun, this, szSvrAddr, iSvrPort, bEnData))
    {
        if(m_pNetClient != NULL)
        {
            m_pNetClient->UnInit(TRUE);
            delete m_pNetClient;
            m_pNetClient = NULL;
        }
        return false;
    }

    bCmdConnect = true;
    return true;
}

void ClientNetworkObject::Stop()
{
    if(m_pNetClient)
    {
        m_pNetClient->UnInit(TRUE);
        delete m_pNetClient;
        m_pNetClient = NULL;
    }

    m_cbSendRound = 0;
    m_cbRecvRound = 0;
    m_dwSendXorKey = 0;
    m_dwRecvXorKey = 0;
    m_dwSendTickCount = 0;
    m_dwRecvTickCount = 0;
    m_dwSendPacketCount = 0;
}

bool ClientNetworkObject::IsConnected()
{
    if(m_pNetClient == NULL) return false;
    return m_pNetClient->IsStarted();
}

void  ClientNetworkObject::ProcessRecvDataFun(char * pData,unsigned long DataLength, void *pContext)
{
    reinterpret_cast<ClientNetworkObject*>(pContext)->OnProcessRecvDataFun(pData, DataLength);
}

void  ClientNetworkObject::OnProcessRecvDataFun(char* pData,unsigned long DataLength)
{
    if(DataLength)
    {
        /** 长度 */
        if(DataLength <= 0) return;
        BYTE pBuffer[BUFFER_SIZE_DEFINE];
        memcpy(pBuffer, pData, DataLength);
        WORD dwSize = CrevasseBuffer((BYTE*)pBuffer, DataLength);

        CMD_Head tagHead;
        memcpy(&tagHead, pBuffer, sizeof(CMD_Head));
        BYTE* pRealData = pBuffer + sizeof(CMD_Head);
        
        /** TODO: 继续格式化 */
        //if(OnProcessRecvData != NULL)
        {
            OnProcessRecvData(tagHead, pRealData);
        }

        //拷贝数据
        m_dwRecvPacketCount++;
    }
}

void ClientNetworkObject::OnProcessRecvData(CMD_Head tagHead, BYTE* pData)
{

}

bool ClientNetworkObject::SendRawData(BYTE* pData,unsigned long Length)
{
    if(m_pNetClient)
    {
        return m_pNetClient->SendMsg((char*)pData, Length);
    }
    else
    {
        return false;
    }
}
bool ClientNetworkObject::SendCommand(WORD wMainCmdID, WORD wSubCmdID, void * pData, WORD wDataSize)
{
    //效验状态
    if (!this->IsConnected()) return false;

    //效验大小
    if (wDataSize>BUFFER_SIZE_DEFINE) return false;

    //效验大小
    if (wDataSize > BUFFER_SIZE_DEFINE) return false;

    //构造数据
    BYTE cbDataBuffer[BUFFER_SIZE_DEFINE];
    CMD_Head * pHead = (CMD_Head *)cbDataBuffer;
    pHead->CommandInfo.wMainCmdID = wMainCmdID;
    pHead->CommandInfo.wSubCmdID = wSubCmdID;
    if (wDataSize > 0 && pData != NULL)
    {
        CopyMemory(pHead + 1, pData, wDataSize);
    }

    //加密数据
    WORD wSendSize = EncryptBuffer(cbDataBuffer, sizeof(CMD_Head) + wDataSize, sizeof(cbDataBuffer));

    //发送数据
    return SendRawData(cbDataBuffer,wSendSize);
}
bool    ClientNetworkObject::SendCommand(WORD wMainCmdID, WORD wSubCmdID)
{
    //效验状态
    if (!this->IsConnected()) return false;

    //构造数据
    BYTE cbDataBuffer[BUFFER_SIZE_DEFINE];
    CMD_Head * pHead = (CMD_Head *)cbDataBuffer;
    pHead->CommandInfo.wMainCmdID = wMainCmdID;
    pHead->CommandInfo.wSubCmdID = wSubCmdID;

    //加密数据
    WORD wSendSize = EncryptBuffer(cbDataBuffer, sizeof(CMD_Head), sizeof(cbDataBuffer));

    //发送数据
    return SendRawData(cbDataBuffer,wSendSize);
}