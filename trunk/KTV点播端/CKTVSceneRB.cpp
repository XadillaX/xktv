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

    /** ���� */
    Tex(m_Panel) = m_pHGE->Texture_Load("rb/panel.png");
    if(Tex(m_Panel) == 0) return false;
    Spr(m_Panel) = new hgeSprite(Tex(m_Panel), 0, 0, TexWidthP(m_Panel), TexHeightP(m_Panel));

    /** ��ť */
    HTEXTURE btn = m_pHGE->Texture_Load("pinyinselect/txtbtn.png");
    GFX_FONT_CONF conf;
    conf.bAntialias = true;
    conf.bBold = true;
    conf.bItalic = false;
    conf.fontSize = 20;
    conf.fontColor = 0xffff7800;
    conf.fontName = "����";

    m_pBackBtn = new CKTVGUITextButton(conf, "����", RB_BACK_BTN_ID, 594, 613, 103, 25, btn);
    m_pPauseBtn = new CKTVGUITextButton(conf, "��ͣ", RB_PAUSE_BTN_ID, 734, 613, 103, 25, btn);
    m_pCutdownBtn = new CKTVGUITextButton(conf, "�и�", RB_CUTDOWN_BTN_ID, 870, 613, 103, 25, btn);
    m_pSuffOrderBtn = new CKTVGUITextButton(conf, "����", RB_SUFF_BTN_ID, 594, 643, 103, 25, btn);

    m_pGUI->AddCtrl((hgeGUIObject*)m_pBackBtn);
    m_pGUI->AddCtrl((hgeGUIObject*)m_pPauseBtn);
    m_pGUI->AddCtrl((hgeGUIObject*)m_pCutdownBtn);
    m_pGUI->AddCtrl((hgeGUIObject*)m_pSuffOrderBtn);

    return true;
}

bool CKTVSceneRB::Update(float fDT)
{
    if(CKTVPlayList::Instance().IsPaused() && m_pPauseBtn->GetText() == "��ͣ")
    {
        m_pPauseBtn->SetText("����");
    }
    else
    if(!CKTVPlayList::Instance().IsPaused() && m_pPauseBtn->GetText() == "����")
    {
        m_pPauseBtn->SetText("��ͣ");
    }

    return false;
}

bool CKTVSceneRB::Render(float fDT)
{
    Spr(m_Panel)->Render(585, 604);

    return false;
}
