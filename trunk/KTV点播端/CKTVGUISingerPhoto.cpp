#include "CKTVGUISingerPhoto.h"

string __singer_base_path = "";

CKTVGUISingerPhoto::CKTVGUISingerPhoto(int _id, int nArtistNo, const char* filename, const char* name, int x, int y, int w, int h, int rw, int rh, const char* fontname, int fontsize, DWORD fontcolor) :
    x(x),
    y(y),
    w(w),
    h(h),
    rw(rw),
    rh(rh),
    m_bDown(false),
    m_nFontColor(fontcolor)
{
    bStatic = true;
	bVisible = true;
	bEnabled = true;

    id = _id;
    m_nArtistNo = nArtistNo;

    Tex(m_Photo) = hge->Texture_Load(string(__singer_base_path + string(filename)).c_str());
    if(0 != Tex(m_Photo))
    {
        Spr(m_Photo) = new hgeSprite(Tex(m_Photo), 0, 0, TexWidthP(m_Photo), TexHeightP(m_Photo));
    }
    else
    {
        Tex(m_Photo) = hge->Texture_Load(SINGER_NO_PHOTO);
        Spr(m_Photo) = new hgeSprite(Tex(m_Photo), 0, 0, TexWidthP(m_Photo), TexHeightP(m_Photo));
    }

    m_szName = name;

    m_pFont = new GfxFont(fontname, fontsize);
    m_pFont->SetColor(fontcolor);

    rect.Set(x, y, x + w, y + h);
}

CKTVGUISingerPhoto::~CKTVGUISingerPhoto(void)
{
    TexRelease(m_Photo);
    if(NULL != m_pFont) delete m_pFont;
}

void CKTVGUISingerPhoto::SetBasePath(string basepath)
{
    __singer_base_path = basepath;
}

bool CKTVGUISingerPhoto::MouseLButton(bool bDown)
{
    m_bDown = bDown;

    return !bDown;
}

void CKTVGUISingerPhoto::Render()
{
    /** Í¸Ã÷¶È */
    if(m_bDown)
    {
        Spr(m_Photo)->SetColor(0x99ffffff);
    }
    else Spr(m_Photo)->SetColor(0xffffffff);

    /** ÕÕÆ¬ */
    float px = (x + (float)(w - rw) / 2);
    if(Spr(m_Photo) != NULL) Spr(m_Photo)->RenderStretch(px, y, px + rw, y + rh);

    /** Ãû×Ö */
    SIZE sz = m_pFont->GetTextSize(C2W(m_szName.c_str()));
    float fy = (y + h - sz.cy);
    float fx = (x + (float)(w - sz.cx) / 2);

    m_pFont->SetColor(0x99000000);
    m_pFont->Print(fx + 1, fy + 1, m_szName.c_str());
    m_pFont->SetColor(m_nFontColor);
    m_pFont->Print(fx, fy, m_szName.c_str());
}
