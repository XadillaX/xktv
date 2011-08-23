//////////////////////////////////////////////////////////////////////////
//
//	KTV键盘GUI接收框类
//
//	Program by 死月(XadillaX) (admin@xcoder.in)
//  Create Date: 2011/08/23
//
//////////////////////////////////////////////////////////////////////////
#ifndef CKTVGUIKEYBOARDRSTBOX_H
#define CKTVGUIKEYBOARDRSTBOX_H

#pragma once
#include "global.h"
#include <hgefont.h>
#include <hgegui.h>
#include <string>
using namespace std;

class CKTVGUIKeyboardRSTBox : public hgeGUIObject
{
public:
    CKTVGUIKeyboardRSTBox(int _id, const char* filename, const char* fontfile, int fontsize, DWORD fontcolor, int x, int y, int nLength = 10);
    virtual ~CKTVGUIKeyboardRSTBox(void);

    void                                SetMaxLength(int nLength);
    bool                                CallChange(char cKey);

    string                              GetData();
    virtual void                        Render();

private:
    string                              m_szData;
    int                                 m_nLength;

    hgeFont*                            m_pFont;
    SpritePair                          m_BG;

    int                                 m_nWidth;
    int                                 m_nHeight;

    int                                 m_nFontSize;
    DWORD                               m_nFontColor;
};

#endif
