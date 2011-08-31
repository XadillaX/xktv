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
#include "cktvguitextbutton.h"
#include "cktvplaylist.h"
#include "fontcn/gfxfont.h"

#define RB_BACK_BTN_ID                  800
#define RB_PAUSE_BTN_ID                 801
#define RB_CUTDOWN_BTN_ID               802
#define RB_SUFF_BTN_ID                  803
#define RB_VOL_SLIDER_ID                804
#define RB_VOL_PLUS_BTN_ID              805
#define RB_VOL_MINUS_BTN_ID             806

class CKTVSceneRB : public CKTVSceneObject
{
public:
    CKTVSceneRB(void);
    virtual ~CKTVSceneRB(void);

    virtual bool                        Update(float fDT);
    virtual bool                        Render(float fDT);
    virtual bool                        Init();

protected:
    SpritePair                          m_Panel;

    CKTVGUITextButton*                  m_pBackBtn;
    CKTVGUITextButton*                  m_pPauseBtn;
    CKTVGUITextButton*                  m_pCutdownBtn;
    CKTVGUITextButton*                  m_pSuffOrderBtn;
    hgeGUISlider*                       m_pVolSlider;
    CKTVGUITextButton*                  m_pVolPlus;
    CKTVGUITextButton*                  m_pVolMinus;

    GfxFont*                            m_pPercentFont;
    GfxFont*                            m_pFont;
    SpritePair                          m_VolumeBG;
};

#endif
