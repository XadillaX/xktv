#include "CKTVSceneAD.h"

/** 注册到工厂 */
namespace
{
    CKTVSceneObject* CreateCKTVSceneObject() { return new CKTVSceneAD(); }
    bool flag = SCENE_FACTORY.Register("AD", CreateCKTVSceneObject);
};

CKTVSceneAD::CKTVSceneAD(void)
{
}

CKTVSceneAD::~CKTVSceneAD(void)
{
}

bool CKTVSceneAD::Init()
{
    CKTVSceneObject::Init();

    m_fDelay = m_pHGE->Ini_GetFloat("ad", "delay", 1000);
    m_nCount = m_pHGE->Ini_GetInt("ad", "count", 0);

    /** 载入图片 */
    for(int i = 0; i < m_nCount; i++)
    {
        /** 获取图片路径 */
        char szFilenameTag[256];
        char* szFilename;

        sprintf(szFilenameTag, "ad%d", i + 1);
        szFilename = m_pHGE->Ini_GetString("ad", szFilenameTag, "");

        SpritePair p;
        p.first = m_pHGE->Texture_Load(szFilename);
        p.second = new hgeSprite(p.first, 0, 0, m_pHGE->Texture_GetWidth(p.first), m_pHGE->Texture_GetHeight(p.first));

        m_Pic.push_back(p);
    }

    m_nCurIdx = 0;
    m_fCurAlpha = 0.0f;
    m_bChanging = false;

    return true;
}

bool CKTVSceneAD::Update(float fDT)
{
    const float fChangingTime = 1.0f;
    static float fTimePast = 0.0;

    /** 计算变换时间 */
    if(!m_bChanging)
    {
        fTimePast += fDT;
        if(fTimePast >= m_fDelay)
        {
            m_bChanging = true;
            fTimePast = 0.0f;
        }
    }
    else
    {
        fTimePast += fDT;
        m_fCurAlpha = fTimePast / fChangingTime;
        if(fTimePast >= fChangingTime)
        {
            m_nCurIdx = (m_nCurIdx + 1) % m_Pic.size();
            m_bChanging = false;
            fTimePast = 0.0f;
        }
    }

    /** 测试转换 */
    if(m_pHGE->Input_GetKeyState(HGEK_LBUTTON)) ENGINE.SetScene("Object");

    return false;
}

bool CKTVSceneAD::Render(float fDT)
{
    if(!m_bChanging)
    {
        if(m_nCurIdx < m_Pic.size())
        {
            SpritePair p = m_Pic[m_nCurIdx];
            if(NULL != p.second)
            {
                float fWidth = p.second->GetWidth();
                float fHeight = p.second->GetHeight();

                float x = (ENGINE.GetWidth() - fWidth) / 2;
                float y = (ENGINE.GetHeight() - fHeight) / 2;

                p.second->SetColor(ARGB(255, 255, 255, 255));
                p.second->Render(x, y);
            }
        }
    }
    else
    {
        if(m_nCurIdx < m_Pic.size())
        {
            SpritePair p = m_Pic[m_nCurIdx];
            if(NULL != p.second)
            {
                float fWidth = p.second->GetWidth();
                float fHeight = p.second->GetHeight();

                float x = (ENGINE.GetWidth() - fWidth) / 2;
                float y = (ENGINE.GetHeight() - fHeight) / 2;

                p.second->SetColor(ARGB(255 * (1 - m_fCurAlpha), 255, 255, 255, 255));
                p.second->Render(x, y);
            }

            p = m_Pic[(m_nCurIdx + 1) % m_Pic.size()];
            if(NULL != p.second)
            {
                float fWidth = p.second->GetWidth();
                float fHeight = p.second->GetHeight();

                float x = (ENGINE.GetWidth() - fWidth) / 2;
                float y = (ENGINE.GetHeight() - fHeight) / 2;

                p.second->SetColor(ARGB(255 * m_fCurAlpha, 255, 255, 255, 255));
                p.second->Render(x, y);
            }
        }
    }

    return false;
}
