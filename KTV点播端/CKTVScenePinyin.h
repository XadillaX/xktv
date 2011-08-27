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
#include "cktvsceneobject.h"
#include "global.h"
#include "hgeguictrls.h"
#include "cktvguikeyboard.h"
#include "cktvguisingerphoto.h"
#include "CKTVModelArtist.h"
#include "cktvmodelsong.h"
#include "fontcn/gfxfont.h"
#include "hgefont.h"
#include "cktvengine.h"
#include "cktvplaylist.h"
#include "cktvscenerb.h"

#define SSS_SONG_PAGE_SIZE                  8
#define SSS_SONG_SEL_START_ID               300
#define SSS_SONG_FIR_START_ID               400
#define SSS_SONG_GUI_PREV_ID                250
#define SSS_SONG_GUI_NEXT_ID                251

enum SHOW_STATE_PINYIN_SELECT
{
    SSPS_SHOW_SONG
};

class CKTVScenePinyin : public CKTVSceneRB
{
public:
    CKTVScenePinyin(void);
    virtual ~CKTVScenePinyin(void);

    virtual bool                           Init();
    virtual bool                           Update(float fDT);
    virtual bool                           Render(float fDT);

    virtual bool                            SongTurnPage(string pinyin, int page);
    void                                    SetShowType(SHOW_STATE_PINYIN_SELECT type);
private:
    bool                                    _SongGUIUpdate(float fDT, int id);

private:
    SpritePair                              m_BG;
    SpritePair                              m_SongPanel;

    vector<CKTVRowSong*>                    m_RSArray;
    vector<hgeGUIButton*>                   m_SelArray;
    vector<hgeGUIButton*>                   m_FirArray;

    GfxFont*                                m_pSongFont;

    CKTVGUIKeyboard*                        m_pKeyboard;
    CKTVGUIKeyboardRSTBox*                  m_pRstBox;

    SHOW_STATE_PINYIN_SELECT                m_ShowState;

    int                                     m_nSongTotPage;
    int                                     m_nSongCurPage;

    hgeFont*                                m_pShowPage;
};
#endif
