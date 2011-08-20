//////////////////////////////////////////////////////////////////////////
//
//	KTV场景管理类
//
//	Program by 死月(XadillaX) (admin@xcoder.in)
//  Create Date: 2011/08/20
//
//////////////////////////////////////////////////////////////////////////
#ifndef CKTVSCENEMANAGER_H
#define CKTVSCENEMANAGER_H
#pragma once

#include "global.h"
#include "CKTVSceneObject.h"
#include <string>
#include <map>

class CKTVSceneManager
{
public:
    CKTVSceneManager(void);
    virtual ~CKTVSceneManager(void);

    bool                                                SetScene(char* szSceneName);
    CKTVSceneObject*                                    GetScene(char* szSceneName);
    bool                                                Update(float fDT);
    bool                                                Render(float fDT);

private:
    CKTVSceneObject*                                    m_pPrevScene;
    CKTVSceneObject*                                    m_pCurrentScene;
    CKTVSceneObject*                                    m_pNextScene;
};
#endif
