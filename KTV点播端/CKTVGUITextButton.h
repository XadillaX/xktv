//////////////////////////////////////////////////////////////////////////
//
//	KTV文字按钮GUI类
//
//	Program by 死月(XadillaX) (admin@xcoder.in)
//  Create Date: 2011/08/20
//
//////////////////////////////////////////////////////////////////////////
#ifndef CKTVGUITEXTBUTTON_H
#define CKTVGUITEXTBUTTON_H

#pragma once
#include "global.h"
#include <hgeguictrls.h>

class CKTVGUITextButton : public hgeGUIButton
{
public:
    CKTVGUITextButton(GFX_FONT_CONF conf, string text, int id, float x, float y, float w, float h, HTEXTURE tex, float tx = 0, float ty = 0);
    virtual ~CKTVGUITextButton(void);
    virtual void	                    Render();

    void                                SetText(string text) { m_szText = text; }
    string                              GetText() { return m_szText; }

protected:
    GfxFont*                            m_pFont;
    string                              m_szText;

    DWORD                               m_dwFontColor;
};

#endif
