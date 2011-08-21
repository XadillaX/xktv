#include "CKTVSceneObject.h"
#include "FontCN/gfxfont.h"

/** 注册到工厂 */
namespace
{
    CKTVSceneObject* CreateCKTVSceneObject() { return new CKTVSceneObject(); }
    bool flag = SCENE_FACTORY.Register("Object", CreateCKTVSceneObject);
};

CKTVSceneObject::CKTVSceneObject(void) :
    m_pHGE(NULL),
    m_State(SCENE_FREE)
{
}

CKTVSceneObject::~CKTVSceneObject(void)
{
    delete m_pGUI;
}

bool CKTVSceneObject::Init()
{
    m_pHGE = hgeCreate(HGE_VERSION);
    m_pGUI = new hgeGUI();

    return true;
}

bool CKTVSceneObject::Update(float fDT)
{
    return false;
}

bool CKTVSceneObject::Render(float fDT)
{
    /** 基类测试显示 */
    GfxFont* font = new GfxFont("微软雅黑", 72, true);

    font->SetColor(0xffffffff);
    SIZE sz = font->GetTextSize(C2W("这是KTV场景基类，请继承它。"));

    float x = (1024 - sz.cx) / 2;
    float y = (768 - sz.cy) / 2;

    font->Print(x, y, "这是KTV场景基类，请继承它。");

    delete font;

    return false;
}

CKTVSCENE_STATE CKTVSceneObject::GetState()
{
    return m_State;
}

void CKTVSceneObject::SetState(CKTVSCENE_STATE state)
{
    m_State = state;
}

bool CKTVSceneObject::ComingUpdate(float fDT)
{
    /** 忽略进入动画，直接设置为DISPLAYING */
    SetState(SCENE_DISPLAYING);
    return Update(fDT);
}

bool CKTVSceneObject::ComingRender(float fDT)
{
    return false;
}

bool CKTVSceneObject::LeavingUpdate(float fDT)
{
    /** 忽略离开动画，直接设置为LEFT */
    SetState(SCENE_LEFT);
    return false;
}

bool CKTVSceneObject::LeavingRender(float fDT)
{
    return false;
}
