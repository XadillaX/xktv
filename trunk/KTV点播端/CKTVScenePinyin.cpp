#include "CKTVScenePinyin.h"

/** 注册到工厂 */
namespace
{
    CKTVSceneObject* CreateCKTVSceneObject() { return new CKTVScenePinyin(); }
    bool flag = SCENE_FACTORY.Register("Pinyin", CreateCKTVSceneObject);
};

CKTVScenePinyin::CKTVScenePinyin(void)
{
    
}

CKTVScenePinyin::~CKTVScenePinyin(void)
{
    TexRelease(m_BG);
}

bool CKTVScenePinyin::Init()
{
    CKTVSceneRB::Init();

    /** 读取配置文件 */
    m_pHGE->System_SetState(HGE_INIFILE, "pinyinselect/pinyinselect.ini");
    
    /** 背景 */
    Tex(m_BG) = m_pHGE->Texture_Load(m_pHGE->Ini_GetString("ui", "background", ""));
    if(0 == Tex(m_BG)) return false;
    Spr(m_BG) = new hgeSprite(Tex(m_BG), 0, 0, TexWidthP(m_BG), TexHeightP(m_BG));

    /** 键盘测试 */
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

    /** 初始化第一页*/
    SongTurnPage("", 1);

    /** 上一页下一页 */
    hgeGUIButton* sbtn_prev = new hgeGUIButton(SSS_SONG_GUI_PREV_ID, 120, 460, 125, 39, m_pHGE->Texture_Load("pinyinselect/pinyinprev.png"), 0, 0);
    hgeGUIButton* sbtn_next = new hgeGUIButton(SSS_SONG_GUI_NEXT_ID, 120 + 125 + 15, 460, 125, 39, m_pHGE->Texture_Load("pinyinselect/pinyinnext.png"), 0, 0);

    m_pGUI->AddCtrl((hgeGUIObject*)sbtn_prev);
    m_pGUI->AddCtrl((hgeGUIObject*)sbtn_next);

    /** 字体 */
    m_pShowPage = new hgeFont("efont/font1.fnt");
    m_pShowPage->SetScale(18.0f / 25.0f);
    m_pSongFont = new GfxFont("微软雅黑", 25);

    SetShowType(SSPS_SHOW_SONG);
    
    return true;
}

bool CKTVScenePinyin::Update(float fDT)
{
    CKTVSceneRB::Update(fDT);

    int id = m_pGUI->Update(fDT);
    if (id != 0 && m_ShowState == SSPS_SHOW_SONG)
    {
        _SongGUIUpdate(fDT, id);
    }
    //switch(id)
    //{
    //case 100:
    //    {
    //        CKTVGUIKeyboardRSTBox* pBox = (CKTVGUIKeyboardRSTBox*)(m_pGUI->GetCtrl(5));
    //        printf("当前: %s...\n", pBox->GetData().c_str());

    //        /** [SQL测试] */
    //        CKTVModelArtist* pCKMA = new CKTVModelArtist();
    //        CKTVRowArtist row[10];
    //        int count = pCKMA->get_artist_info_by_pinyin(pBox->GetData(), row, 1, 10);

    //        for(int i = 0; i < count; i++) cout << row[i].ArtistName << endl;

    //        cout << "共 " << pCKMA->get_max_page_by_pinyin(pBox->GetData(), 10) << " 页, " << pCKMA->get_artist_count_by_pinyin(pBox->GetData()) << " 条数据\n";
    //        cout << "当前第 1 页, 本页有 " << count << " 条数据." << endl;
    //        delete pCKMA;
    //        /** [/SQL测试] */
    //        
    //        break;
    //    }

    //default: break;
    //}

    return false;
}

bool CKTVScenePinyin::_SongGUIUpdate(float fDT, int id)
{
    /** 常规GUI */
    switch(id)
    {
    case 100:                                       ///< 键盘的ID
        {
            SetShowType(SSPS_SHOW_SONG);
            SongTurnPage(m_pRstBox->GetData(), 1);
            break;
        }

    case SSS_SONG_GUI_PREV_ID:                      ///< 上一页
        {
            SongTurnPage(m_pRstBox->GetData(), m_nSongCurPage + 1);
            break;
        }

    case SSS_SONG_GUI_NEXT_ID:                      ///< 下一页
        {
            SongTurnPage(m_pRstBox->GetData(), m_nSongCurPage + 1);
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

bool CKTVScenePinyin::Render(float fDT)
{
    /** 背景 */
    float fBGx = (ENGINE.GetWidth() - TexWidthP(m_BG)) / 2;
    float fBGy = (ENGINE.GetHeight() - TexHeightP(m_BG)) / 2;
    Spr(m_BG)->Render(fBGx, fBGy);

    if (SSPS_SHOW_SONG == m_ShowState)
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

    SetShowType(SSPS_SHOW_SONG);

    CKTVSceneRB::Render(fDT);

    return false;
}

bool CKTVScenePinyin::SongTurnPage(string pinyin, int page)
{
    CKTVModelSong* pMS = new CKTVModelSong();

    int totalpage = pMS->get_max_page_by_pinyin(pinyin, SSS_SONG_PAGE_SIZE);
    if(page > totalpage) page = 1;
    else
    if(page < 1) page = totalpage;

    /** 获取记录 */
    CKTVRowSong row[SSS_SONG_PAGE_SIZE];
    int count = pMS->get_song_by_pinyin(pinyin, row, page, SSS_SONG_PAGE_SIZE);

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

void CKTVScenePinyin::SetShowType(SHOW_STATE_PINYIN_SELECT type)
{
    if(m_ShowState == type) return;
    m_ShowState = type;
    if(type == SSPS_SHOW_SONG)
    {
        hgeGUIButton* btn;

        /*************************************************************************/
        btn = (hgeGUIButton*)(m_pGUI->GetCtrl(SSS_SONG_GUI_PREV_ID));
        btn->bVisible = true;
        btn->bEnabled = true;

        btn = (hgeGUIButton*)(m_pGUI->GetCtrl(SSS_SONG_GUI_NEXT_ID));
        btn->bVisible = true;
        btn->bEnabled = true;

        for(int i = 0; i < m_SelArray.size(); i++)
        {
            m_SelArray[i]->bEnabled = m_SelArray[i]->bVisible = true;
            m_FirArray[i]->bEnabled = m_FirArray[i]->bVisible = true;
        }
    }
}