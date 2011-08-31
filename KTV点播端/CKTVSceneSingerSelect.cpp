#include "CKTVSceneSingerSelect.h"

/** 注册到工厂 */
namespace
{
    CKTVSceneObject* CreateCKTVSceneObject() { return new CKTVSceneSingerSelect(); }
    bool flag = SCENE_FACTORY.Register("Singer", CreateCKTVSceneObject);
};

CKTVSceneSingerSelect::CKTVSceneSingerSelect(void)
{
}

CKTVSceneSingerSelect::~CKTVSceneSingerSelect(void)
{
    TexRelease(m_BG);
    TexRelease(m_SongPanel);
}

bool CKTVSceneSingerSelect::Init()
{
    CKTVSceneRB::Init();

    /** 读取配置文件 */
    m_pHGE->System_SetState(HGE_INIFILE, "singerselect/singerselect.ini");

    /** 背景 */
    Tex(m_BG) = m_pHGE->Texture_Load(m_pHGE->Ini_GetString("ui", "background", ""));
    if(0 == Tex(m_BG)) return false;
    Spr(m_BG) = new hgeSprite(Tex(m_BG), 0, 0, TexWidthP(m_BG), TexHeightP(m_BG));

    /** 键盘 */
    char fn1[256], fn2[256], fn3[256];
    strcpy(fn1, m_pHGE->Ini_GetString("ui", "keyboarditem", ""));
    strcpy(fn2, m_pHGE->Ini_GetString("ui", "keyboard", ""));
    strcpy(fn3, m_pHGE->Ini_GetString("ui", "keybox", ""));
    m_pKeyboard = new CKTVGUIKeyboard(37, 555, 100, fn2, fn1);
    m_pGUI->AddCtrl((hgeGUIObject*)m_pKeyboard);
    m_pRstBox = new CKTVGUIKeyboardRSTBox(5, fn3, "efont/font1.fnt", 18, 0xffffffff, 585, 555);
    m_pKeyboard->BindBox(m_pRstBox);
    m_pGUI->AddCtrl((hgeGUIObject*)m_pRstBox);

    Tex(m_SongPanel) = m_pHGE->Texture_Load(m_pHGE->Ini_GetString("ui", "songpanel", ""));
    if(Tex(m_SongPanel) == 0) Spr(m_SongPanel) = NULL;
    else Spr(m_SongPanel) = new hgeSprite(Tex(m_SongPanel), 0, 0, TexWidthP(m_SongPanel), TexHeightP(m_SongPanel));

    /** 照片路径 */
    CKTVGUISingerPhoto::SetBasePath(m_pHGE->Ini_GetString("system", "photopath", ""));

    /** 初始化照片 */
    SingerTurnPage("", 1);

    /** 上一页下一页 */
    hgeGUIButton* btn_prev = new hgeGUIButton(SINGER_GUI_PREV_ID, 80, 500, 125, 39, m_pHGE->Texture_Load("singerselect/singerprev.png"), 0, 0);
    hgeGUIButton* btn_next = new hgeGUIButton(SINGER_GUI_NEXT_ID, 80 + 125 + 15, 500, 125, 39, m_pHGE->Texture_Load("singerselect/singernext.png"), 0, 0);
    hgeGUIButton* sbtn_prev = new hgeGUIButton(SSS_SONG_GUI_PREV_ID, 120, 460, 125, 39, m_pHGE->Texture_Load("singerselect/singerprev.png"), 0, 0);
    hgeGUIButton* sbtn_next = new hgeGUIButton(SSS_SONG_GUI_NEXT_ID, 120 + 125 + 15, 460, 125, 39, m_pHGE->Texture_Load("singerselect/singernext.png"), 0, 0);
    hgeGUIButton* sbtn_back = new hgeGUIButton(SSS_SONG_GUI_BACK_ID, 120 + (125 + 15) * 2, 460, 50, 39, m_pHGE->Texture_Load("singerselect/back.png"), 0, 0);

    m_pGUI->AddCtrl((hgeGUIObject*)btn_prev);
    m_pGUI->AddCtrl((hgeGUIObject*)btn_next);
    m_pGUI->AddCtrl((hgeGUIObject*)sbtn_prev);
    m_pGUI->AddCtrl((hgeGUIObject*)sbtn_next);
    m_pGUI->AddCtrl((hgeGUIObject*)sbtn_back);

    /** 字体 */
    m_pShowPage = new hgeFont("efont/font1.fnt");
    m_pShowPage->SetScale(18.0f / 25.0f);
    m_pSongFont = new GfxFont("微软雅黑", 25);

    SetShowType(SSSS_SHOW_SINGER);

    return true;
}

bool CKTVSceneSingerSelect::Update(float fDT)
{
    CKTVSceneRB::Update(fDT);

    int id = m_pGUI->Update(fDT);
    if(id != 0 && m_ShowState == SSSS_SHOW_SINGER)
    {
        _SingerGUIUpdate(fDT, id);
    }
    else
    if(id != 0 && m_ShowState == SSSS_SHOW_SONG)
    {
        _SongGUIUpdate(fDT, id);
    }

    return false;
}

bool CKTVSceneSingerSelect::_SongGUIUpdate(float fDT, int id)
{
    /** 常规GUI */
    switch(id)
    {
    case 100:                                       ///< 键盘的ID
        {
            SetShowType(SSSS_SHOW_SINGER);
            SingerTurnPage(m_pRstBox->GetData(), 1);
            break;
        }

    case SSS_SONG_GUI_PREV_ID:
        {
            SongTurnPage(m_nSingerID, m_nSongCurPage + 1);
            break;
        }

    case SSS_SONG_GUI_NEXT_ID:
        {
            SongTurnPage(m_nSingerID, m_nSongCurPage + 1);
            break;
        }

    case SSS_SONG_GUI_BACK_ID:
        {
            SetShowType(SSSS_SHOW_SINGER);
            break;
        }

    case RB_BACK_BTN_ID:                            ///< 返回
        {
            ENGINE.SetScene("Function");
            break;
        }

    case RB_PAUSE_BTN_ID:                           ///< 播放/暂停
        {
            CKTVPlayList::Instance().ChangePlayStatus();
            break;
        }

    case RB_CUTDOWN_BTN_ID:
        {
            CKTVPlayList::Instance().SendCutdownMsg();
            break;
        }

    case RB_SUFF_BTN_ID:
        {
            CKTVPlayList::Instance().SuffOrder();
            break;
        }

    default: break;
    }

    /** 选歌 */
    if(id >= SSS_SONG_SEL_START_ID && id < SSS_SONG_SEL_START_ID + SSS_SONG_PAGE_SIZE)
    {
        CKTVRowSong* rowsong = m_RSArray[id - SSS_SONG_SEL_START_ID];

        CKTVPlayList::Instance().AddSongToLast(*rowsong);
    }

    /** 优歌 */
    if(id >= SSS_SONG_FIR_START_ID && id < SSS_SONG_FIR_START_ID + SSS_SONG_PAGE_SIZE)
    {
        CKTVRowSong* rowsong = m_RSArray[id - SSS_SONG_FIR_START_ID];

        CKTVPlayList::Instance().AddSongToFirst(*rowsong);
    }

    return false;
}

bool CKTVSceneSingerSelect::_SingerGUIUpdate(float fDT, int id)
{
    /** 常规GUI */
    switch(id)
    {
    case 100:                                       ///< 键盘的ID
        {
            SetShowType(SSSS_SHOW_SINGER);
            SingerTurnPage(m_pRstBox->GetData(), 1);
            break;
        }

    case SINGER_GUI_PREV_ID:                        ///< 上一页
        {
            SetShowType(SSSS_SHOW_SINGER);
            SingerTurnPage(m_pRstBox->GetData(), m_nSingerCurPage + 1);
            break;
        }

    case SINGER_GUI_NEXT_ID:                        ///< 下一页
        {
            SetShowType(SSSS_SHOW_SINGER);
            SingerTurnPage(m_pRstBox->GetData(), m_nSingerCurPage - 1);
            break;
        }

    case RB_BACK_BTN_ID:                            ///< 返回
        {
            ENGINE.SetScene("Function");
            break;
        }

    case RB_PAUSE_BTN_ID:                           ///< 播放/暂停
        {
            CKTVPlayList::Instance().ChangePlayStatus();
            break;
        }

    case RB_CUTDOWN_BTN_ID:
        {
            CKTVPlayList::Instance().SendCutdownMsg();
            break;
        }

    case RB_SUFF_BTN_ID:
        {
            CKTVPlayList::Instance().SuffOrder();
            break;
        }

    default: break;
    }

    /** 歌手按钮GUI */
    if(id >= PHOTO_GUI_START_ID && id < PHOTO_GUI_START_ID + PHOTO_GUI_PAGE_SIZE)
    {
        m_nSingerID = m_SPArray[id - PHOTO_GUI_START_ID]->GetArtistNo();

        m_nSongCurPage = 1;
        SongTurnPage(m_nSingerID, 1);
        SetShowType(SSSS_SHOW_SONG);
    }

    return false;
}

bool CKTVSceneSingerSelect::Render(float fDT)
{
    Spr(m_BG)->Render(0, 0);

    CKTVSceneRB::Render(fDT);

    if(SSSS_SHOW_SONG == m_ShowState)
    {
        /** 歌背景 */
        if(NULL != Spr(m_SongPanel))
        {
            Spr(m_SongPanel)->Render(37, 37);
        }

        /** 歌的字 */
        float s_start_x = 120.0f, s_start_y = 72.0f, s_space = 48.0f;
        float a_start_x = 855.0f, a_start_y = 72.0f, a_space = 48.0f;
        for(int i = 0; i < m_RSArray.size(); i++)
        {
            float x = s_start_x, y = s_start_y + s_space * i;

            m_pSongFont->SetColor(0x99000000);
            m_pSongFont->Print(x + 1, y + 1, m_RSArray[i]->SongName.c_str());
            m_pSongFont->SetColor(0xffff0099);
            m_pSongFont->Print(x, y, m_RSArray[i]->SongName.c_str());

            SIZE sz = m_pSongFont->GetTextSize(C2W(m_RSArray[i]->ArtistName.c_str()));
            x = a_start_x - sz.cx, y = a_start_y + a_space * i;
            m_pSongFont->SetColor(0x99000000);
            m_pSongFont->Print(x + 1, y + 1, m_RSArray[i]->ArtistName.c_str());
            m_pSongFont->SetColor(0xffff7800);
            m_pSongFont->Print(x, y, m_RSArray[i]->ArtistName.c_str());
        }

        /** 页码 */
        char buf[128];
        sprintf(buf, "%d / %d", m_nSongCurPage, m_nSongTotPage);
        m_pShowPage->SetColor(0x99000000);
        m_pShowPage->printf(120 + (125 + 15) * 2 + 1 + 15 + 50, 460 + 10 + 1, HGETEXT_LEFT, buf);
        m_pShowPage->SetColor(0xffffffff);
        m_pShowPage->printf(120 + (125 + 15) * 2 + 15 + 50, 460 + 10, HGETEXT_LEFT, buf);
    }

    m_pGUI->Render();

    /** 选歌时 */
    if(SSSS_SHOW_SINGER == m_ShowState)
    {
        /** 页码 */
        char buf[128];
        sprintf(buf, "%d / %d", m_nSingerCurPage, m_nSingerTotPage);
        m_pShowPage->SetColor(0x99000000);
        m_pShowPage->printf(80 + (125 + 15) * 2 + 1, 500 + 10 + 1, HGETEXT_LEFT, buf);
        m_pShowPage->SetColor(0xffffffff);
        m_pShowPage->printf(80 + (125 + 15) * 2, 500 + 10, HGETEXT_LEFT, buf);
    }

    return false;
}

bool CKTVSceneSingerSelect::SongTurnPage(int artistno, int page)
{
    CKTVModelSong* pMS = new CKTVModelSong();

    int totalpage = pMS->get_max_page_by_artistno(artistno, SSS_SONG_PAGE_SIZE);
    if(page > totalpage) page = 1;
    else
    if(page < 1) page = totalpage;

    /** 获取记录 */
    CKTVRowSong row[SSS_SONG_PAGE_SIZE];
    int count = pMS->get_song_by_artistno(artistno, row, page, SSS_SONG_PAGE_SIZE);

    /** 删除原歌 */
    while(!m_RSArray.empty())
    {
        CKTVRowSong* r = m_RSArray[m_RSArray.size() - 1];

        int sel_id = m_RSArray.size() - 1 + SSS_SONG_SEL_START_ID;
        int fir_id = m_RSArray.size() - 1 + SSS_SONG_FIR_START_ID;

        hgeGUIButton* sel_btn = (hgeGUIButton*)m_pGUI->GetCtrl(sel_id);
        hgeGUIButton* fir_btn = (hgeGUIButton*)m_pGUI->GetCtrl(sel_id);
        if(sel_btn != NULL) m_pGUI->DelCtrl(sel_id);
        if(fir_btn != NULL) m_pGUI->DelCtrl(fir_id);

        delete r;
        m_RSArray.pop_back();
        m_SelArray.pop_back();
        m_FirArray.pop_back();
    }

    /** 新一页歌 */
    const float first_sel_x = 870.0f, first_sel_y = 74.0f, first_sel_space = 48.0f;
    const float first_fir_x = 910.0f, first_fir_y = 74.0f, first_fir_space = 48.0f;
    for(int i = 0; i < count; i++)
    {
        CKTVRowSong* r = new CKTVRowSong();
        *r = row[i];

        m_RSArray.push_back(r);

        int sel_id = i + SSS_SONG_SEL_START_ID;
        int fir_id = i + SSS_SONG_FIR_START_ID;

        hgeGUIButton* sel_btn = new hgeGUIButton(sel_id, first_sel_x, first_sel_y + first_sel_space * i, 32, 30, m_pHGE->Texture_Load("singerselect/sel.png"), 0, 0);
        hgeGUIButton* fir_btn = new hgeGUIButton(fir_id, first_fir_x, first_fir_y + first_fir_space * i, 32, 30, m_pHGE->Texture_Load("singerselect/fir.png"), 0, 0);

        m_pGUI->AddCtrl((hgeGUIObject*)sel_btn);
        m_pGUI->AddCtrl((hgeGUIObject*)fir_btn);
        m_SelArray.push_back(sel_btn);
        m_FirArray.push_back(fir_btn);
    }

    delete pMS;

    m_nSongTotPage = totalpage;
    m_nSongCurPage = page;

    return true;
}

bool CKTVSceneSingerSelect::SingerTurnPage(string pinyin, int page)
{
    CKTVModelArtist* pMA = new CKTVModelArtist();
    
    /** 页数 */
    int totalpage = pMA->get_max_page_by_pinyin(pinyin, PHOTO_GUI_PAGE_SIZE);
    //if(page > totalpage)
    //{
    //    delete pMA;
    //    return false;
    //}
    if(page > totalpage)
    {
        page = 1;
    }
    else
    if(page < 1) page = totalpage;

    /** 获取记录 */
    CKTVRowArtist row[15];
    int count = pMA->get_artist_info_by_pinyin(pinyin, row, page, PHOTO_GUI_PAGE_SIZE);
    
    /** 删除原有记录 */
    for(int i = m_SPArray.size() - 1; i >= 0; i--)
    {
        m_pGUI->DelCtrl(m_SPArray[i]->id);
        //delete m_SPArray[i];
        m_SPArray.pop_back();
    }

    /** 新建记录 */
    float x = 80, y = 112;
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 5 && i * 5 + j < count; j++)
        {
            int id = i * 5 + j;
            CKTVGUISingerPhoto* pSP = new CKTVGUISingerPhoto(id + PHOTO_GUI_START_ID,
                row[id].ArtistNo, row[id].ArtistPhoto.c_str(), row[id].ArtistName.c_str(),
                x + (j * (125 + 15)), y + (i * (170 + 20)), 125, 170, 125, 150, "黑体"
                );

            m_pGUI->AddCtrl((hgeGUIObject*)pSP);

            m_SPArray.push_back(pSP);
        }
    }

    m_nSingerCurPage = page;
    m_nSingerTotPage = totalpage;

    delete pMA;

    return true;
}

void CKTVSceneSingerSelect::SetShowType(SHOW_STATE_SINGER_SELECT type)
{
    if(m_ShowState == type) return;
    m_ShowState = type;

    if(type == SSSS_SHOW_SONG)
    {
        hgeGUIButton* btn;
        
        btn = (hgeGUIButton*)(m_pGUI->GetCtrl(SINGER_GUI_PREV_ID));
        btn->bVisible = false;
        btn->bEnabled = false;

        btn = (hgeGUIButton*)(m_pGUI->GetCtrl(SINGER_GUI_NEXT_ID));
        btn->bVisible = false;
        btn->bEnabled = false;

        for(int i = 0; i < m_SPArray.size(); i++) m_SPArray[i]->bEnabled = m_SPArray[i]->bVisible = false;

        /*************************************************************************/
        btn = (hgeGUIButton*)(m_pGUI->GetCtrl(SSS_SONG_GUI_PREV_ID));
        btn->bVisible = true;
        btn->bEnabled = true;

        btn = (hgeGUIButton*)(m_pGUI->GetCtrl(SSS_SONG_GUI_NEXT_ID));
        btn->bVisible = true;
        btn->bEnabled = true;

        btn = (hgeGUIButton*)(m_pGUI->GetCtrl(SSS_SONG_GUI_BACK_ID));
        btn->bVisible = true;
        btn->bEnabled = true;

        for(int i = 0; i < m_SelArray.size(); i++)
        {
            m_SelArray[i]->bEnabled = m_SelArray[i]->bVisible = true;
            m_FirArray[i]->bEnabled = m_FirArray[i]->bVisible = true;
        }
    }
    else
    {
        hgeGUIButton* btn;
        
        btn = (hgeGUIButton*)(m_pGUI->GetCtrl(SINGER_GUI_PREV_ID));
        btn->bVisible = true;
        btn->bEnabled = true;

        btn = (hgeGUIButton*)(m_pGUI->GetCtrl(SINGER_GUI_NEXT_ID));
        btn->bVisible = true;
        btn->bEnabled = true;

        for(int i = 0; i < m_SPArray.size(); i++) m_SPArray[i]->bEnabled = m_SPArray[i]->bVisible = true;

        /*************************************************************************/
        btn = (hgeGUIButton*)(m_pGUI->GetCtrl(SSS_SONG_GUI_PREV_ID));
        btn->bVisible = false;
        btn->bEnabled = false;

        btn = (hgeGUIButton*)(m_pGUI->GetCtrl(SSS_SONG_GUI_NEXT_ID));
        btn->bVisible = false;
        btn->bEnabled = false;

        btn = (hgeGUIButton*)(m_pGUI->GetCtrl(SSS_SONG_GUI_BACK_ID));
        btn->bVisible = false;
        btn->bEnabled = false;

        for(int i = 0; i < m_SelArray.size(); i++)
        {
            m_SelArray[i]->bEnabled = m_SelArray[i]->bVisible = false;
            m_FirArray[i]->bEnabled = m_FirArray[i]->bVisible = false;
        }
    }
}
