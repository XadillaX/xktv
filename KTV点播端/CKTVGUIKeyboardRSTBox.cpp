#include "CKTVGUIKeyboardRSTBox.h"

CKTVGUIKeyboardRSTBox::CKTVGUIKeyboardRSTBox(int _id, const char* filename, const char* fontfile, int fontsize, DWORD fontcolor, int x, int y, int nLength) :
    m_szData(""),
    m_nLength(nLength)
{
    id = _id;
	bStatic = true;
	bVisible = true;
	bEnabled = true;

    /** 背景 */
    Tex(m_BG) = hge->Texture_Load(filename);
    Spr(m_BG) = new hgeSprite(Tex(m_BG), 0, 0, TexWidthP(m_BG), TexHeightP(m_BG));
    m_nWidth = TexWidthP(m_BG);
    m_nHeight = TexHeightP(m_BG);

    /** 字体 */
    m_pFont = new hgeFont(fontfile);
    m_nFontSize = fontsize;
    m_nFontColor = fontcolor;
    m_pFont->SetScale((float)((float)fontsize / 25.0f));
    m_pFont->SetColor(m_nFontColor);

    /** 矩形 */
    rect.Set(x, y, x + m_nWidth, y + m_nHeight);
}

CKTVGUIKeyboardRSTBox::~CKTVGUIKeyboardRSTBox(void)
{
}

void CKTVGUIKeyboardRSTBox::SetMaxLength(int nLength)
{
    m_nLength = nLength;
}

bool CKTVGUIKeyboardRSTBox::CallChange(char cKey)
{
    /** 退格 */
    if(cKey == 8)
    {
        if(m_szData.length() > 0)
        {
            m_szData = m_szData.substr(0, m_szData.length() - 1);
            return true;
        }
        else return false;
    }
    /** 增加 */
    else
    {
        if(m_szData.length() < m_nLength)
        {
            m_szData += cKey;
            return true;
        }
        else return false;
    }

    return true;
}

void CKTVGUIKeyboardRSTBox::Render()
{
    Spr(m_BG)->Render(rect.x1, rect.y1);

    /** 字体y */
    float y = rect.y1 + (m_nHeight - m_pFont->GetHeight());
    m_pFont->printf(rect.x1 + 10, y, HGETEXT_LEFT, m_szData.c_str());
}

string CKTVGUIKeyboardRSTBox::GetData()
{
    return m_szData;
}
