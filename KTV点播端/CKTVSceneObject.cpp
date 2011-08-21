#include "CKTVSceneObject.h"
#include "FontCN/gfxfont.h"

/** ע�ᵽ���� */
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
    /** ���������ʾ */
    GfxFont* font = new GfxFont("΢���ź�", 72, true);

    font->SetColor(0xffffffff);
    SIZE sz = font->GetTextSize(C2W("����KTV�������࣬��̳�����"));

    float x = (1024 - sz.cx) / 2;
    float y = (768 - sz.cy) / 2;

    font->Print(x, y, "����KTV�������࣬��̳�����");

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
    /** ���Խ��붯����ֱ������ΪDISPLAYING */
    SetState(SCENE_DISPLAYING);
    return Update(fDT);
}

bool CKTVSceneObject::ComingRender(float fDT)
{
    return false;
}

bool CKTVSceneObject::LeavingUpdate(float fDT)
{
    /** �����뿪������ֱ������ΪLEFT */
    SetState(SCENE_LEFT);
    return false;
}

bool CKTVSceneObject::LeavingRender(float fDT)
{
    return false;
}
