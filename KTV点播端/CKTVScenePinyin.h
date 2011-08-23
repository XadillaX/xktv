//////////////////////////////////////////////////////////////////////////
//
//	KTV拼音选歌场景类
//
//	Program by 死月(XadillaX) (admin@xcoder.in)
//  Create Date: 2011/08/20
//
//////////////////////////////////////////////////////////////////////////
#ifndef CKTVSCENEPINYIN_H
#define CKTVSCENEPINYIN_H
#pragma once
#include "global.h"
#include "cktvengine.h"
#include "cktvsceneobject.h"
#include "CKTVGUIKeyboard.h"
#include "cktvguikeyboardrstbox.h"
#include "cktvmodelartist.h"

class CKTVScenePinyin : public CKTVSceneObject
{
public:
    CKTVScenePinyin(void);
    virtual ~CKTVScenePinyin(void);

    virtual bool                        Init();
    virtual bool                        Update(float fDT);
    virtual bool                        Render(float fDT);

protected:
    SpritePair                          m_BG;
};
#endif
