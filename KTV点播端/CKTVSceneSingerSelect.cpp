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
}

bool CKTVSceneSingerSelect::Init()
{
    CKTVSceneObject::Init();

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

    /** 照片路径 */
    CKTVGUISingerPhoto::SetBasePath(m_pHGE->Ini_GetString("system", "photopath", ""));

    /** 初始化照片 */
    SingerTurnPage("", 1);

    m_ShowState = SSSS_SHOW_SINGER;

    /** 上一页下一页 */
    hgeGUIButton* btn_prev = new hgeGUIButton(SINGER_GUI_PREV_ID, 80, 500, 125, 39, m_pHGE->Texture_Load("singerselect/singerprev.png"), 0, 0);
    hgeGUIButton* btn_next = new hgeGUIButton(SINGER_GUI_PREV_ID, 80 + 125 + 15, 500, 125, 39, m_pHGE->Texture_Load("singerselect/singernext.png"), 0, 0);

    m_pGUI->AddCtrl((hgeGUIObject*)btn_prev);
    m_pGUI->AddCtrl((hgeGUIObject*)btn_next);

    m_pShowPage = new hgeFont("efont/font1.fnt");
    m_pShowPage->SetScale(18.0f / 25.0f);

    return true;
}

bool CKTVSceneSingerSelect::Update(float fDT)
{
    int id = m_pGUI->Update(fDT);
    if(id != 0)
    {
        switch(id)
        {
        case 100:                                       ///< 键盘的ID
            {
                SetShowType(SSSS_SHOW_SINGER);
                SingerTurnPage(m_pRstBox->GetData(), 1);
                break;
            }

        case SINGER_GUI_PREV_ID:
            {
                SetShowType(SSSS_SHOW_SINGER);
                SingerTurnPage(m_pRstBox->GetData(), m_nSingerCurPage + 1);
                break;
            }

        case SINGER_GUI_NEXT_ID:
            {
                SetShowType(SSSS_SHOW_SINGER);
                SingerTurnPage(m_pRstBox->GetData(), m_nSingerCurPage - 1);
                break;
            }

        default: break;
        }
    }

    return false;
}

bool CKTVSceneSingerSelect::Render(float fDT)
{
    Spr(m_BG)->Render(0, 0);
    m_pGUI->Render();

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
}
