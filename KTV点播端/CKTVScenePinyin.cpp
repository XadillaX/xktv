#include "CKTVScenePinyin.h"

/** ×¢²áµ½¹¤³§ */
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

    /** ¶ÁÈ¡ÅäÖÃ */
    m_pHGE->System_SetState(HGE_INIFILE, "pinyinselect/pinyinselect.ini");
    char* filename = m_pHGE->Ini_GetString("ui", "background", "");
    m_BG.first = m_pHGE->Texture_Load(filename);
    if(m_BG.first == 0) return false;
    m_BG.second = new hgeSprite(m_BG.first, 0, 0, TexWidthP(m_BG), TexHeightP(m_BG));

    /** ¼üÅÌ²âÊÔ */
    char fn1[256], fn2[256];
    strcpy(fn1, m_pHGE->Ini_GetString("ui", "keyboarditem", ""));
    strcpy(fn2, m_pHGE->Ini_GetString("ui", "keyboard", ""));
    CKTVGUIKeyboard* pGK = new CKTVGUIKeyboard(37, 555, 100, fn2, fn1);
    m_pGUI->AddCtrl((hgeGUIObject*)pGK);

    return true;
}

bool CKTVScenePinyin::Update(float fDT)
{
    int id = m_pGUI->Update(fDT);
    switch(id)
    {
    case 100:
        {
            CKTVGUIKeyboard* pGK = (CKTVGUIKeyboard*)(m_pGUI->GetCtrl(100));
            printf("%c ±»°´ÏÂÁË...\n", pGK->GetKey());

            break;
        }

    default: break;
    }

    return false;
}

bool CKTVScenePinyin::Render(float fDT)
{
    /** ±³¾° */
    float fBGx = (ENGINE.GetWidth() - TexWidthP(m_BG)) / 2;
    float fBGy = (ENGINE.GetHeight() - TexHeightP(m_BG)) / 2;
    Spr(m_BG)->Render(fBGx, fBGy);

    m_pGUI->Render();

    return false;
}
