#include "CKTVSceneRB.h"

CKTVSceneRB::CKTVSceneRB(void)
{
}

CKTVSceneRB::~CKTVSceneRB(void)
{
}

bool CKTVSceneRB::Init()
{
    CKTVSceneObject::Init();

    Tex(m_Panel) = m_pHGE->Texture_Load("rb/panel.png");
    if(Tex(m_Panel) == 0) return false;
    Spr(m_Panel) = new hgeSprite(Tex(m_Panel), 0, 0, TexWidthP(m_Panel), TexHeightP(m_Panel));

    return true;
}

bool CKTVSceneRB::Update(float fDT)
{

    return false;
}

bool CKTVSceneRB::Render(float fDT)
{
    Spr(m_Panel)->Render(585, 604);

    return false;
}
