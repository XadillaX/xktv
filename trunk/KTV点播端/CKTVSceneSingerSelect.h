//////////////////////////////////////////////////////////////////////////
//
//	KTV歌手选歌场景类
//
//	Program by 死月(XadillaX) (admin@xcoder.in)
//  Create Date: 2011/08/20
//
//////////////////////////////////////////////////////////////////////////
#ifndef CKTVSCENESINGERSELECT_H
#define CKTVSCENESINGERSELECT_H

#pragma once
#include "cktvsceneobject.h"
#include "global.h"
#include "hgeguictrls.h"
#include "cktvguikeyboard.h"
#include "cktvguisingerphoto.h"
#include "CKTVModelArtist.h"
#include "hgefont.h"

#define SINGER_GUI_PREV_ID                  220
#define SINGER_GUI_NEXT_ID                  221
#define PHOTO_GUI_START_ID                  105
#define PHOTO_GUI_PAGE_SIZE                 10

enum SHOW_STATE_SINGER_SELECT
{
    SSSS_SHOW_SINGER,
    SSSS_SHOW_SONG
};

class CKTVSceneSingerSelect : public CKTVSceneObject
{
public:
    CKTVSceneSingerSelect(void);
    virtual ~CKTVSceneSingerSelect(void);

    virtual bool                            Init();
    virtual bool                            Update(float fDT);
    virtual bool                            Render(float fDT);

    virtual bool                            SingerTurnPage(string pinyin, int page);
    void                                    SetShowType(SHOW_STATE_SINGER_SELECT type);

private:
    SpritePair                              m_BG;

    vector<CKTVGUISingerPhoto*>             m_SPArray;

    CKTVGUIKeyboard*                        m_pKeyboard;
    CKTVGUIKeyboardRSTBox*                  m_pRstBox;

    int                                     m_nSingerTotPage;
    int                                     m_nSingerCurPage;
    SHOW_STATE_SINGER_SELECT                m_ShowState;

    hgeFont*                                m_pShowPage;
};

#endif
