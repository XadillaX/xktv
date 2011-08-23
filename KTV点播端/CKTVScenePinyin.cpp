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
    CKTVSceneObject::Init();

    /** 读取配置 */
    m_pHGE->System_SetState(HGE_INIFILE, "pinyinselect/pinyinselect.ini");
    char* filename = m_pHGE->Ini_GetString("ui", "background", "");
    m_BG.first = m_pHGE->Texture_Load(filename);
    if(m_BG.first == 0) return false;
    m_BG.second = new hgeSprite(m_BG.first, 0, 0, TexWidthP(m_BG), TexHeightP(m_BG));

    /** 键盘测试 */
    char fn1[256], fn2[256];
    strcpy(fn1, m_pHGE->Ini_GetString("ui", "keyboarditem", ""));
    strcpy(fn2, m_pHGE->Ini_GetString("ui", "keyboard", ""));
    CKTVGUIKeyboard* pGK = new CKTVGUIKeyboard(37, 555, 100, fn2, fn1);
    m_pGUI->AddCtrl((hgeGUIObject*)pGK);
    CKTVGUIKeyboardRSTBox* pBox = new CKTVGUIKeyboardRSTBox(5, "pinyinselect/keybox.png", "efont/font1.fnt", 18, 0xffffffff, 585, 555);
    pGK->BindBox(pBox);
    m_pGUI->AddCtrl((hgeGUIObject*)pBox);

    return true;
}

bool CKTVScenePinyin::Update(float fDT)
{
    int id = m_pGUI->Update(fDT);
    switch(id)
    {
    case 100:
        {
            CKTVGUIKeyboardRSTBox* pBox = (CKTVGUIKeyboardRSTBox*)(m_pGUI->GetCtrl(5));
            printf("当前: %s...\n", pBox->GetData().c_str());

            /** [SQL测试] */
            CKTVModelArtist* pCKMA = new CKTVModelArtist();
            CKTVRowArtist row[10];
            int count = pCKMA->get_artist_info_by_pinyin(pBox->GetData(), row, 1, 10);

            for(int i = 0; i < count; i++) cout << row[i].ArtistName << endl;

            cout << "共 " << pCKMA->get_max_page_by_pinyin(pBox->GetData(), 10) << " 页, " << pCKMA->get_artist_count_by_pinyin(pBox->GetData()) << " 条数据\n";
            cout << "当前第 1 页, 本页有 " << count << " 条数据." << endl;
            delete pCKMA;
            /** [/SQL测试] */
            
            break;
        }

    default: break;
    }

    return false;
}

bool CKTVScenePinyin::Render(float fDT)
{
    /** 背景 */
    float fBGx = (ENGINE.GetWidth() - TexWidthP(m_BG)) / 2;
    float fBGy = (ENGINE.GetHeight() - TexHeightP(m_BG)) / 2;
    Spr(m_BG)->Render(fBGx, fBGy);

    m_pGUI->Render();

    return false;
}
