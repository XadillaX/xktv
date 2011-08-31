//////////////////////////////////////////////////////////////////////////
//
//	KTV机器信息类
//
//	Program by 死月(XadillaX) (admin@xcoder.in)
//  Create Date: 2011/08/25
//
//////////////////////////////////////////////////////////////////////////
#ifndef CKTVMACHINEINFO_H
#define CKTVMACHINEINFO_H

#pragma once
#include "global.h"
#include "cktvmodelmachine.h"
#include <time.h>

class CKTVPlayList;
class CKTVMachineInfo
{
public:
    CKTVMachineInfo(string no = "");
    ~CKTVMachineInfo(void);

    bool                                SetMachineNo(string no);
    bool                                Update();

    bool                                StartListen();
    bool                                EndListen();
    bool                                IsListening() { return m_bIsListening; }

    /** 获取信息函数 */
    CKTVRowMachine                      GetMachineInfo()
    {
        ::EnterCriticalSection(&m_CriticalSection);
        CKTVRowMachine info = m_MachineInfo;
        ::LeaveCriticalSection(&m_CriticalSection);

        return m_MachineInfo;
    }
    int                                 GetMinuteLeft();
    string                              GetStatus() { return m_MachineInfo.Status; }

private:
    string                              m_nMachineID;
    bool                                m_bIsListening;
    HANDLE                              m_hThread;

    CKTVModelMachine                    m_Machine;
    CKTVRowMachine                      m_MachineInfo;

    CRITICAL_SECTION                    m_CriticalSection;
};

#endif
