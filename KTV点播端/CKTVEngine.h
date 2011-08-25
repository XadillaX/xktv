//////////////////////////////////////////////////////////////////////////
//
//	KTV引擎单件类
//
//	Program by 死月(XadillaX) (admin@xcoder.in)
//  Create Date: 2011/08/20
//
//////////////////////////////////////////////////////////////////////////
#ifndef CKTVENGINE_H
#define CKTVENGINE_H

#pragma once
#include "global.h"
#include "cktvscenemanager.h"
#include "cktvmachineinfo.h"

class CKTVEngine : public Singleton<CKTVEngine>
{
public:
    CKTVEngine(void);
    virtual ~CKTVEngine(void);

    bool                        init();
    bool                        start();
    bool                        close();
    bool                        Update(float fDeltaTime);
    bool                        Render(float fDeltaTime);

    bool                        SetScene(char* szSceneName);

    HGE*                        GetHGE();

    int                         GetWidth() { return m_nWidth; }
    int                         GetHeight() { return m_nHeight; }

protected:
    HGE*                        m_pHGE;
    CKTVSceneManager*           m_pSceneManager;
    CKTVMachineInfo*            m_pMachineInfo;

    int                         m_nWidth;
    int                         m_nHeight;
    int                         m_nFPS;
    int                         m_nBPP;
    bool                        m_bWindowed;
    bool                        m_bCursor;

    char*                       m_szLogfile;

    char                        m_szDSNName[256];
    char                        m_szUsername[256];
    char                        m_szPassword[256];
};

#endif
