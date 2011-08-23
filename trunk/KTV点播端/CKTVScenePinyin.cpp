#include "CKTVScenePinyin.h"

/** ע�ᵽ���� */
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

    /** ��ȡ���� */
    m_pHGE->System_SetState(HGE_INIFILE, "pinyinselect/pinyinselect.ini");
    char* filename = m_pHGE->Ini_GetString("ui", "background", "");
    m_BG.first = m_pHGE->Texture_Load(filename);
    if(m_BG.first == 0) return false;
    m_BG.second = new hgeSprite(m_BG.first, 0, 0, TexWidthP(m_BG), TexHeightP(m_BG));

    /** ���̲��� */
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
            printf("��ǰ: %s...\n", pBox->GetData().c_str());

            /** [SQL����] */
            CKTVModelArtist* pCKMA = new CKTVModelArtist();
            CKTVRowArtist row[10];
            int count = pCKMA->get_artist_info_by_pinyin(pBox->GetData(), row, 1, 10);

            for(int i = 0; i < count; i++) cout << row[i].ArtistName << endl;

            cout << "�� " << pCKMA->get_max_page_by_pinyin(pBox->GetData(), 10) << " ҳ, " << pCKMA->get_artist_count_by_pinyin(pBox->GetData()) << " ������\n";
            cout << "��ǰ�� 1 ҳ, ��ҳ�� " << count << " ������." << endl;
            delete pCKMA;
            /** [/SQL����] */
            
            break;
        }

    default: break;
    }

    return false;
}

bool CKTVScenePinyin::Render(float fDT)
{
    /** ���� */
    float fBGx = (ENGINE.GetWidth() - TexWidthP(m_BG)) / 2;
    float fBGy = (ENGINE.GetHeight() - TexHeightP(m_BG)) / 2;
    Spr(m_BG)->Render(fBGx, fBGy);

    m_pGUI->Render();

    return false;
}
