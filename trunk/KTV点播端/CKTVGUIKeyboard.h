//////////////////////////////////////////////////////////////////////////
//
//	KTVº¸≈ÃGUI¿‡
//
//	Program by À¿‘¬(XadillaX) (admin@xcoder.in)
//  Create Date: 2011/08/21
//
//////////////////////////////////////////////////////////////////////////
#ifndef CKTVGUIKEYBOARD_H
#define CKTYGUIKEYBOARD_H
#pragma once
#include "global.h"
#include <hgegui.h>
#include "cktvguikeyboarditem.h"

#define KEYBOARD_WIDTH                      541
#define KEYBOARD_HEIGHT                     190

class CKTVGUIKeyboard : public hgeGUI, public hgeGUIObject
{
public:
    CKTVGUIKeyboard(int _x, int _y, int _id, const char* bgfilename, const char* keyfilaneme);
    virtual ~CKTVGUIKeyboard(void);

    char                                    GetKey();
    virtual void                            Render();
    virtual bool                            MouseLButton(bool bDown);

private:
    void                                    __InitKey(const char* filename);

protected:
    int x;
    int y;

    SpritePair                              m_BG;
    char                                    m_cCurKey;
};
#endif
