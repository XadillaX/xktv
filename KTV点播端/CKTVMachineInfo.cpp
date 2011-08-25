#include "CKTVMachineInfo.h"

DWORD WINAPI MachineInfoListen(LPVOID lpvThreadParm)
{
    CKTVMachineInfo* pInfo = (CKTVMachineInfo*)lpvThreadParm;

    while(pInfo->IsListening())
    {
        while(!pInfo->Update()) { Sleep(1); }
        printf("当前状态: %s. 离关机时间还有 %d 分钟...\n", pInfo->GetStatus().c_str(), pInfo->GetMinuteLeft());

        /** 休眠半分钟(半分钟更新一次信息) */
        Sleep(30 * 1000);
    }

    return 0;
}

CKTVMachineInfo::CKTVMachineInfo(string no) :
    m_nMachineID(no),
    m_bIsListening(false)
{
    ::InitializeCriticalSection(&m_CriticalSection);
}

CKTVMachineInfo::~CKTVMachineInfo(void)
{
    EndListen();
}

bool CKTVMachineInfo::SetMachineNo(string no)
{
    m_nMachineID = no;
    return m_Machine.get_machine_info(no, &m_MachineInfo);
}

bool CKTVMachineInfo::Update()
{
    if(m_nMachineID == "") return false;

    ::EnterCriticalSection(&m_CriticalSection);
    bool flag = m_Machine.get_machine_info(m_nMachineID, &m_MachineInfo);
    ::LeaveCriticalSection(&m_CriticalSection);
    
    return flag;
}

int CKTVMachineInfo::GetMinuteLeft()
{
    tm end;

    ::EnterCriticalSection(&m_CriticalSection);
    end.tm_year = m_MachineInfo.ShutTime.year - 1900;
    end.tm_mon = m_MachineInfo.ShutTime.month - 1;
    end.tm_mday = m_MachineInfo.ShutTime.day;
    end.tm_hour = m_MachineInfo.ShutTime.hour;
    end.tm_min = m_MachineInfo.ShutTime.minute;
    end.tm_sec = m_MachineInfo.ShutTime.second;
    ::LeaveCriticalSection(&m_CriticalSection);

    time_t endtime = mktime(&end);
    time_t starttime = time(NULL);

    //printf(asctime(&start));
    //printf(asctime(&end));
    //printf("%d\n", m_MachineInfo.ShutTime.hour);

    return (int)difftime(endtime, starttime) / 60;

    return 0;
}

bool CKTVMachineInfo::StartListen()
{
    if(m_bIsListening) return false;

    m_hThread = CreateThread(NULL, 0, MachineInfoListen, (LPVOID)this, 0, 0);
    if(m_hThread)
    {
        m_bIsListening = true;
    }

    return (bool)m_hThread;
}

bool CKTVMachineInfo::EndListen()
{
    if(!m_bIsListening) return false;

    m_bIsListening = false;
    return true;
}
