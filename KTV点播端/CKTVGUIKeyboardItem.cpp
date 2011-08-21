#include "CKTVGUIKeyboardItem.h"
#include <string>

CKTVGUIKeyboardItem::CKTVGUIKeyboardItem(char key, int x, int y, int w, int h, const char* filename, const char* fontname, int fontsize, DWORD fontcolor)
{
    id = (int)key;
    bStatic = false;
    bVisible = true;
    bEnabled = true;
    m_bOldState = false;
    rect.Set(x, y, x + w, y + h);
    m_cKey = key;

    Tex(m_Tex) = hge->Texture_Load(filename);
    Ani(m_Tex) = new hgeAnimation(Tex(m_Tex), 2, 10, 0, 0, w, h);
    Ani(m_Tex)->SetFrame(0);

    m_dwFontColor = fontcolor;
    m_pFont = new GfxFont(fontname, fontsize);
    m_pFont->SetColor(fontcolor);
}

CKTVGUIKeyboardItem::~CKTVGUIKeyboardItem(void)
{
    if(m_pFont != NULL) delete m_pFont;
}

bool CKTVGUIKeyboardItem::MouseLButton(bool bDown)
{
    if(bDown)
    {
        Ani(m_Tex)->SetFrame(1);
        m_bOldState = bDown;
        return false;
    }
    else
    if(!bDown)
    {
        Ani(m_Tex)->SetFrame(0);
        float x, y;
        hge->Input_GetMousePos(&x, &y);
        if(m_bOldState == true && rect.TestPoint(x, y))
        {
            m_bOldState = bDown;
            return true;
        }

        m_bOldState = bDown;
        return false;
    }
}

void CKTVGUIKeyboardItem::Render()
{
    float x = rect.x1, y = rect.y1, w = rect.x2 - rect.x1, h = rect.y2 - rect.y1;
    Ani(m_Tex)->Render(x, y);

    string dis = (m_cKey == 8) ? "ÍË" : "";
    if(dis.length() == 0) dis += m_cKey;
    SIZE sz = m_pFont->GetTextSize(C2W(dis.c_str()));
    x = (x + (w - sz.cx) / 2);
    y = (y + (h - sz.cy) / 2);

    m_pFont->SetColor(ARGB(150, 0, 0, 0));
    m_pFont->Print(x + 1, y + 1, dis.c_str());
    m_pFont->SetColor(m_dwFontColor);
    m_pFont->Print(x, y, dis.c_str());
}

char CKTVGUIKeyboardItem::GetKey()
{
    return m_cKey;
}
