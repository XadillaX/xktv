//////////////////////////////////////////////////////////////////////////
//
//	KTV右下角GUI Scene基类
//
//	Program by 死月(XadillaX) (admin@xcoder.in)
//  Create Date: 2011/08/26
//
//////////////////////////////////////////////////////////////////////////
#ifndef CKTVSCENERB_H
#define CKTVSCENERB_H

#pragma once
#include "global.h"
#include "cktvsceneobject.h"

class CKTVSceneRB : public CKTVSceneObject
{
public:
    CKTVSceneRB(void);
    virtual ~CKTVSceneRB(void);

    virtual bool                        Update(float fDT);
    virtual bool                        Render(float fDT);
    virtual bool                        Init();

private:
    SpritePair                          m_Panel;
};

#endif
