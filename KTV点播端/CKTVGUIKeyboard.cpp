#include "CKTVGUIKeyboard.h"

CKTVGUIKeyboard::CKTVGUIKeyboard(int _x, int _y, int _id, const char* bgfilename, const char* keyfilename) :
    m_pBox(NULL)
{
    id = _id;
    bStatic = false;
    bVisible = true;
    bEnabled = true;
    x = _x, y = _y;

    Tex(m_BG) = hgeGUIObject::hge->Texture_Load(bgfilename);
    Spr(m_BG) = new hgeSprite(Tex(m_BG), 0, 0, KEYBOARD_WIDTH, KEYBOARD_HEIGHT);

    rect.Set(x, y, x + KEYBOARD_WIDTH, y + KEYBOARD_HEIGHT);
    __InitKey(keyfilename);

    m_cCurKey = 0;
}

CKTVGUIKeyboard::~CKTVGUIKeyboard(void)
{
    TexRelease(m_BG);
}

char CKTVGUIKeyboard::GetKey()
{
    return m_cCurKey;
}

bool CKTVGUIKeyboard::MouseLButton(bool bDown)
{
    bool rst = false;
    int id = hgeGUI::Update(hgeGUIObject::hge->Timer_GetDelta());
    m_cCurKey = (char)id;
    if(id != 0 && m_pBox != NULL)
    {
        rst = m_pBox->CallChange((char)id);
    }

    return rst;
}

void CKTVGUIKeyboard::Render()
{
    Spr(m_BG)->Render(x, y);
    hgeGUI::Render();
}

void CKTVGUIKeyboard::__InitKey(const char* filename)
{
    char lay1[11] = "QWERTYUIOP";
    char lay2[11] = "ASDFGHJKL";
    char lay3[11] = "ZXCVBNM";
    lay3[7] = 8;
    lay3[8] = '\0';

    /** 第一行 */
    float lx = x + 13, ly = y + 8;
    for(int i = 0; i < 10; i++)
    {
        CKTVGUIKeyboardItem* pKI = new CKTVGUIKeyboardItem(lay1[i], lx, ly, 53, 52, filename, "黑体", 35, 0xffffffff);
        this->AddCtrl((hgeGUIObject*)pKI);
        lx += 52;
    }

    /** 第二行 */
    lx = x + 38, ly = y + 67;
    for(int i = 0; i < 9; i++)
    {
        CKTVGUIKeyboardItem* pKI = new CKTVGUIKeyboardItem(lay2[i], lx, ly, 53, 52, filename, "黑体", 35, 0xffffffff);
        this->AddCtrl((hgeGUIObject*)pKI);
        lx += 52;
    }

    /** 第三行 */
    lx = x + 66, ly = y + 129;
    for(int i = 0; i < 8; i++)
    {
        CKTVGUIKeyboardItem* pKI = new CKTVGUIKeyboardItem(lay3[i], lx, ly, 53, 52, filename, "黑体", 35, 0xffffffff);
        this->AddCtrl((hgeGUIObject*)pKI);
        lx += 52;
    }
}

void CKTVGUIKeyboard::BindBox(CKTVGUIKeyboardRSTBox* box)
{
    m_pBox = box;
}
