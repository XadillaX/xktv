//////////////////////////////////////////////////////////////////////////
//
//	KTV∏Ë ÷’’∆¨GUI¿‡
//
//	Program by À¿‘¬(XadillaX) (admin@xcoder.in)
//  Create Date: 2011/08/20
//
//////////////////////////////////////////////////////////////////////////
#ifndef CKTVGUISINGERPHOTO_H
#define CKTVGUISINGERPHOTO_H

#pragma once
#include <hgegui.h>
#include "global.h"
#include "fontcn/gfxfont.h"
#include <vector>

#define SINGER_NO_PHOTO                     "singerselect/no_photo.png"

class CKTVGUISingerPhoto : public hgeGUIObject
{
public:
    CKTVGUISingerPhoto(int _id, int nArtistNo, const char* filename, const char* name, int x, int y, int w, int h, int rw, int rh, const char* fontname = "Œ¢»Ì—≈∫⁄", int fontsize = 18, DWORD fontcolor = 0xffffffff);
    virtual ~CKTVGUISingerPhoto(void);

    static void                             SetBasePath(string basepath);
    virtual bool                            MouseLButton(bool bDown);
    virtual void                            Render();

    int                                     GetArtistNo() { return m_nArtistNo; }

private:
    int                                     m_nArtistNo;

    SpritePair                              m_Photo;
    string                                  m_szName;

    GfxFont*                                m_pFont;
    DWORD                                   m_nFontColor;

    bool                                    m_bDown;

    int                                     x;
    int                                     y;
    int                                     w;
    int                                     h;
    int                                     rw;
    int                                     rh;
};

#endif
