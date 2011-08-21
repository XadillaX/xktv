//////////////////////////////////////////////////////////////////////////
//
//	KTVº¸≈ÃGUI∞¥º¸¿‡
//
//	Program by À¿‘¬(XadillaX) (admin@xcoder.in)
//  Create Date: 2011/08/21
//
//////////////////////////////////////////////////////////////////////////
#ifndef CKTVGUIKEYBOARDITEM_H
#define CKTVGUIKEYBOARDITEM_H
#pragma once
#include "global.h"
#include "fontcn/gfxfont.h"
#include <hgegui.h>

class CKTVGUIKeyboardItem : public hgeGUIObject
{
public:
    CKTVGUIKeyboardItem(char key, int x, int y, int w, int h, const char* filename, const char* fontname, int fontsize, DWORD fontcolor);
    virtual ~CKTVGUIKeyboardItem(void);

    virtual void                        Render();
	virtual bool                        MouseLButton(bool bDown);

    char                                GetKey();

protected:
    char                                m_cKey;
    GfxFont*                            m_pFont;

    AnimationPair                       m_Tex;

    bool                                m_bOldState;
    DWORD                               m_dwFontColor;
};
#endif
