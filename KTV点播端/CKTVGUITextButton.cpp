#include "CKTVGUITextButton.h"

CKTVGUITextButton::CKTVGUITextButton(GFX_FONT_CONF conf, string text, int id, float x, float y, float w, float h, HTEXTURE tex, float tx, float ty) :
    hgeGUIButton(id, x, y, w, h, tex, tx, ty),
    m_pFont(NULL),
    m_szText(text)
{
    m_pFont = conf.CreateFont();
    m_dwFontColor = conf.fontColor;
}

CKTVGUITextButton::~CKTVGUITextButton(void)
{
    if(m_pFont != NULL) delete m_pFont;
}

void CKTVGUITextButton::Render()
{
    hgeGUIButton::Render();

    float x = rect.x1, w = rect.x2 - rect.x1;
    float y = rect.y1, h = rect.y2 - rect.y1;

    SIZE sz = m_pFont->GetTextSize(C2W(m_szText.c_str()));
    float fx = x + (w - sz.cx) / 2;
    float fy = y + (h - sz.cy) / 2;

    m_pFont->SetColor(0x99000000);
    m_pFont->Print(fx + 1, fy + 1, m_szText.c_str());
    m_pFont->SetColor(m_dwFontColor);
    m_pFont->Print(fx, fy, m_szText.c_str());
}
