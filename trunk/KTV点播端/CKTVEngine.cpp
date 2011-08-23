#include "CKTVEngine.h"
#include "commonclass.h"

bool FrameFunc();
bool RenderFunc();

CKTVEngine::CKTVEngine(void) :
    m_pHGE(NULL),
    m_pSceneManager(NULL)
{
}

CKTVEngine::~CKTVEngine(void)
{
}

bool CKTVEngine::init()
{
    /** ´´½¨äÖÈ¾ÒýÇæHGE */
    m_pHGE = hgeCreate(HGE_VERSION);
    if(NULL == m_pHGE) return false;

    /** ¶ÁÈ¡ÅäÖÃ */
    m_pHGE->System_SetState(HGE_INIFILE, CONFIG_FILE);
    m_nWidth = m_pHGE->Ini_GetInt("display", "width", 1024);
    m_nHeight = m_pHGE->Ini_GetInt("display", "height", 768);
    m_nBPP = m_pHGE->Ini_GetInt("display", "bpp", 32);
    m_nFPS = m_pHGE->Ini_GetInt("display", "fps", 100);
    m_bWindowed = (bool)m_pHGE->Ini_GetInt("display", "windowed", 0);
    m_bCursor = (bool)m_pHGE->Ini_GetInt("display", "cursor", 0);
    m_szLogfile = m_pHGE->Ini_GetString("system", "logfile", "ktv.log");

    /** ÅäÖÃHGE */
    m_pHGE->System_SetState(HGE_SCREENWIDTH, m_nWidth);
    m_pHGE->System_SetState(HGE_SCREENHEIGHT, m_nHeight);
    m_pHGE->System_SetState(HGE_SCREENBPP, m_nBPP);
    m_pHGE->System_SetState(HGE_FPS, m_nFPS);
    m_pHGE->System_SetState(HGE_WINDOWED, m_bWindowed);
    m_pHGE->System_SetState(HGE_HIDEMOUSE, !m_bCursor);
    m_pHGE->System_SetState(HGE_LOGFILE, m_szLogfile);

    m_pHGE->System_SetState(HGE_FRAMEFUNC, FrameFunc);
    m_pHGE->System_SetState(HGE_RENDERFUNC, RenderFunc);
    m_pHGE->System_SetState(HGE_TITLE, KTV_TITLE);
    m_pHGE->System_SetState(HGE_SHOWSPLASH, false);

    m_pSceneManager = new CKTVSceneManager();

    /** SQL Á´½Ó */
    strcpy(m_szDSNName, m_pHGE->Ini_GetString("database", "DSN", "ktv"));
    strcpy(m_szUsername, m_pHGE->Ini_GetString("database", "username", "sa"));
    strcpy(m_szPassword, m_pHGE->Ini_GetString("database", "password", ""));
    XModelConnection::Instance().Initialize(m_szDSNName, m_szUsername, m_szPassword);
    if(!XModelConnection::Instance().Connect()) return false;

    return m_pHGE->System_Initiate();
}

bool CKTVEngine::SetScene(char* szSceneName)
{
    return m_pSceneManager->SetScene(szSceneName);
}

bool CKTVEngine::start()
{
    return m_pHGE->System_Start();
}

bool CKTVEngine::close()
{
    m_pHGE->System_Shutdown();
    m_pHGE->Release();

    return true;
}

HGE* CKTVEngine::GetHGE()
{
    return m_pHGE;
}

bool CKTVEngine::Update(float fDeltaTime)
{
    return m_pSceneManager->Update(fDeltaTime);
}

bool CKTVEngine::Render(float fDeltaTime)
{
    m_pHGE->Gfx_BeginScene();
    m_pHGE->Gfx_Clear(0);

    bool flag = m_pSceneManager->Render(fDeltaTime);

    m_pHGE->Gfx_EndScene();

    return flag;
}

/*************************************************************************/
bool RenderFunc()
{
    return ENGINE.Render(ENGINE.GetHGE()->Timer_GetDelta());
}

bool FrameFunc()
{
    return ENGINE.Update(ENGINE.GetHGE()->Timer_GetDelta());
}
