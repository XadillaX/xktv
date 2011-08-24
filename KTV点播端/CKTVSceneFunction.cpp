#include "CKTVSceneFunction.h"
#include <hgeguictrls.h>

/** 注册到工厂 */
namespace
{
    CKTVSceneObject* CreateCKTVSceneObject() { return new CKTVSceneFunction(); }
    bool flag = SCENE_FACTORY.Register("Function", CreateCKTVSceneObject);
};

CKTVSceneFunction::CKTVSceneFunction(void) :
    m_fBackTime(0.0f)
{
}

CKTVSceneFunction::~CKTVSceneFunction(void)
{
    delete m_BG.second;
    m_BG.second = NULL;
    m_pHGE->Texture_Free(m_BG.first);
}

bool CKTVSceneFunction::Init()
{
    CKTVSceneObject::Init();

    m_pHGE->System_SetState(HGE_INIFILE, "function/function.ini");
    m_fBackTime = m_pHGE->Ini_GetFloat("scene", "backtime", 5.0f);

    /** 背景 */
    char* szBGFilename = m_pHGE->Ini_GetString("ui", "background", "");
    m_BG.first = m_pHGE->Texture_Load(szBGFilename);
    if(0 == m_BG.first) return false;
    m_BG.second = new hgeSprite(m_BG.first, 0, 0, TexWidth(m_BG.first), TexHeight(m_BG.first));

    /** GUI */
    hgeGUIButton* pPYDG = new hgeGUIButton(1, 114, 326, 117, 116, m_pHGE->Texture_Load("function/pydg.png"), 0, 0);
    hgeGUIButton* pGSDG = new hgeGUIButton(2, 795, 326, 117, 116, m_pHGE->Texture_Load("function/gsdg.png"), 0, 0);

    m_pGUI->AddCtrl((hgeGUIObject*)pPYDG);
    m_pGUI->AddCtrl((hgeGUIObject*)pGSDG);

    return true;
}

bool CKTVSceneFunction::Update(float fDT)
{
    static float fNowBackTime = 0.0f;
    fNowBackTime += fDT;
    if(fNowBackTime >= m_fBackTime)
    {
        fNowBackTime = 0.0f;
        ENGINE.SetScene("AD");

        return false;
    }

    /** GUI */
    int id = m_pGUI->Update(fDT);
    switch(id)
    {
    case 1:
        {
            /** 重置计时器 */
            fNowBackTime = 0.0f;

            printf("进入 拼音点歌...\n");
            ENGINE.SetScene("Pinyin");

            break;
        }

    case 2:
        {
            /** 重置计时器 */
            fNowBackTime = 0.0f;

            printf("进入 歌手点歌...\n");
            ENGINE.SetScene("Singer");
        }

    default: break;
    }

    return false;
}

bool CKTVSceneFunction::Render(float fDT)
{
    float fWidth = TexWidth(m_BG.first);
    float fHeight = TexHeight(m_BG.first);
    float x = (ENGINE.GetWidth() - fWidth) / 2;
    float y = (ENGINE.GetHeight() - fHeight) / 2;
    m_BG.second->Render(x, y);

    m_pGUI->Render();

    return false;
}
