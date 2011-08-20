//////////////////////////////////////////////////////////////////////////
//
//	KTV��������
//
//	Program by ����(XadillaX) (admin@xcoder.in)
//  Create Date: 2011/08/20
//
//////////////////////////////////////////////////////////////////////////
#ifndef CKTVSCENEOBJECT_H
#define CKTVSCENEOBJECT_H
#pragma once

#include "global.h"

enum CKTVSCENE_STATE
{
    SCENE_FREE,
    SCENE_COMING,
    SCENE_DISPLAYING,
    SCENE_LEAVING,
    SCENE_LEFT
};

#define SCENE_FACTORY               (ObjectFactory<CKTVSceneObject>::Instance())

class CKTVSceneObject
{
public:
    CKTVSceneObject(void);
    virtual ~CKTVSceneObject(void);

    virtual bool                        Init();
    virtual bool                        Update(float fDT);
    virtual bool                        Render(float fDT);

    /** ���������뿪ʱ�ĸ��º����Լ���Ⱦ���� */
    virtual bool                        ComingUpdate(float fDT);
    virtual bool                        ComingRender(float fDT);
    virtual bool                        LeavingUpdate(float fDT);
    virtual bool                        LeavingRender(float fDT);

    virtual CKTVSCENE_STATE             GetState();
    virtual void                        SetState(CKTVSCENE_STATE state);                      

protected:
    HGE*                                m_pHGE;
    CKTVSCENE_STATE                     m_State;
};

#endif
