#include "CKTVSceneRB.h"

CKTVSceneRB::CKTVSceneRB(void)
{
}

CKTVSceneRB::~CKTVSceneRB(void)
{
    TexRelease(m_Panel);
}

bool CKTVSceneRB::Init()
{
    CKTVSceneObject::Init();

    /** 背景 */
    Tex(m_Panel) = m_pHGE->Texture_Load("rb/panel.png");
    if(Tex(m_Panel) == 0) return false;
    Spr(m_Panel) = new hgeSprite(Tex(m_Panel), 0, 0, TexWidthP(m_Panel), TexHeightP(m_Panel));

    /** 按钮 */
    HTEXTURE btn = m_pHGE->Texture_Load("pinyinselect/txtbtn.png");
    HTEXTURE slider = m_pHGE->Texture_Load("rb/vol_bar_in.png");
    HTEXTURE volbtn = m_pHGE->Texture_Load("rb/vol.png");
    GFX_FONT_CONF conf;
    conf.bAntialias = true;
    conf.bBold = true;
    conf.bItalic = false;
    conf.fontSize = 18;
    conf.fontColor = 0xffff7800;
    conf.fontName = "黑体";

    m_pBackBtn = new CKTVGUITextButton(conf, "返回", RB_BACK_BTN_ID, 594, 613, 103, 25, btn);
    m_pPauseBtn = new CKTVGUITextButton(conf, "暂停", RB_PAUSE_BTN_ID, 734, 613, 103, 25, btn);
    m_pCutdownBtn = new CKTVGUITextButton(conf, "切歌", RB_CUTDOWN_BTN_ID, 870, 613, 103, 25, btn);
    m_pSuffOrderBtn = new CKTVGUITextButton(conf, "乱入＞▽＜", RB_SUFF_BTN_ID, 594, 643, 103, 25, btn);

    m_pVolSlider = new hgeGUISlider(RB_VOL_SLIDER_ID, 661 + 5, 717 + 3, 255, 13, slider, 0, 0, 255, 13);
    m_pVolSlider->SetMode(0, 100, HGESLIDER_BAR);
    m_pVolSlider->SetValue(CKTVPlayList::Instance().GetVolume());

    m_pVolMinus = new CKTVGUITextButton(conf, "-", RB_VOL_MINUS_BTN_ID, 927, 715, 25.5, 25, volbtn);
    m_pVolPlus = new CKTVGUITextButton(conf, "+", RB_VOL_PLUS_BTN_ID, 954, 715, 25.5, 25, volbtn);

    m_pGUI->AddCtrl((hgeGUIObject*)m_pBackBtn);
    m_pGUI->AddCtrl((hgeGUIObject*)m_pPauseBtn);
    m_pGUI->AddCtrl((hgeGUIObject*)m_pCutdownBtn);
    m_pGUI->AddCtrl((hgeGUIObject*)m_pSuffOrderBtn);
    m_pGUI->AddCtrl((hgeGUIObject*)m_pVolSlider);
    m_pGUI->AddCtrl((hgeGUIObject*)m_pVolMinus);
    m_pGUI->AddCtrl((hgeGUIObject*)m_pVolPlus);

    /** 字体 */
    m_pFont = new GfxFont("微软雅黑", 20);
    m_pPercentFont = new GfxFont("宋体", 12, 0, 0, 0);
    m_pPercentFont->SetColor(0xffffffff);

    /** 音量背景 */
    Tex(m_VolumeBG) = m_pHGE->Texture_Load("rb/vol_bar.png");
    if(Tex(m_VolumeBG) == 0) return false;
    Spr(m_VolumeBG) = new hgeSprite(Tex(m_VolumeBG), 0, 0, TexWidthP(m_VolumeBG), TexHeightP(m_VolumeBG));

    return true;
}

bool CKTVSceneRB::Update(float fDT)
{
    if(CKTVPlayList::Instance().IsPaused() && m_pPauseBtn->GetText() == "暂停")
    {
        m_pPauseBtn->SetText("播放");
    }
    else
    if(!CKTVPlayList::Instance().IsPaused() && m_pPauseBtn->GetText() == "播放")
    {
        m_pPauseBtn->SetText("暂停");
    }

    //int id = m_pGUI->Update(fDT);
    //switch(id)
    //{
    //    case 
    //}

    return false;
}

bool CKTVSceneRB::Render(float fDT)
{
    Spr(m_Panel)->Render(585, 604);

    /** 音量 */
    m_pFont->SetColor(0x99000000);
    m_pFont->Print(594 + 1, 717 + 1 - 5, "音量：");
    m_pFont->SetColor(0xffffffff);
    m_pFont->Print(594, 717 - 5, "音量：");
    Spr(m_VolumeBG)->Render(661, 717);

    /** 百分比 */
    char percent[32];
    sprintf(percent, "%.2f%%", m_pVolSlider->GetValue());
    SIZE sz = m_pPercentFont->GetTextSize(C2W(percent));
    sprintf(percent, "%.2f", m_pVolSlider->GetValue());
    m_pPercentFont->Print(661 + 5 + (255 - sz.cx) / 2, 717 + 3 + (13 - sz.cy) / 2, "%s%%", percent);

    return false;
}
