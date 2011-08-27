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
#include "cktvmodelsong.h"
#include "fontcn/gfxfont.h"
#include "hgefont.h"
#include "cktvplaylist.h"
#include "cktvscenerb.h"

#define SINGER_GUI_PREV_ID                  220
#define SINGER_GUI_NEXT_ID                  221
#define PHOTO_GUI_START_ID                  105
#define PHOTO_GUI_PAGE_SIZE                 10
#define SSS_SONG_PAGE_SIZE                  8
#define SSS_SONG_SEL_START_ID               300
#define SSS_SONG_FIR_START_ID               400
#define SSS_SONG_GUI_PREV_ID                250
#define SSS_SONG_GUI_NEXT_ID                251
#define SSS_SONG_GUI_BACK_ID                252

enum SHOW_STATE_SINGER_SELECT
{
    SSSS_SHOW_SINGER,
    SSSS_SHOW_SONG
};

class CKTVSceneSingerSelect : public CKTVSceneRB
{
public:
    CKTVSceneSingerSelect(void);
    virtual ~CKTVSceneSingerSelect(void);

    virtual bool                            Init();
    virtual bool                            Update(float fDT);
    virtual bool                            Render(float fDT);

    virtual bool                            SongTurnPage(int artistno, int page);
    virtual bool                            SingerTurnPage(string pinyin, int page);
    void                                    SetShowType(SHOW_STATE_SINGER_SELECT type);

private:
    bool                                    _SingerGUIUpdate(float fDT, int id);
    bool                                    _SongGUIUpdate(float fDT, int id);

private:
    SpritePair                              m_BG;
    SpritePair                              m_SongPanel;

    vector<CKTVGUISingerPhoto*>             m_SPArray;
    vector<CKTVRowSong*>                    m_RSArray;
    vector<hgeGUIButton*>                   m_SelArray;
    vector<hgeGUIButton*>                   m_FirArray;

    GfxFont*                                m_pSongFont;

    CKTVGUIKeyboard*                        m_pKeyboard;
    CKTVGUIKeyboardRSTBox*                  m_pRstBox;

    int                                     m_nSingerTotPage;
    int                                     m_nSingerCurPage;
    SHOW_STATE_SINGER_SELECT                m_ShowState;

    int                                     m_nSingerID;
    int                                     m_nSongTotPage;
    int                                     m_nSongCurPage;

    hgeFont*                                m_pShowPage;
};

#endif
