#include "CKTVEngine.h"
#include "commonclass.h"

bool FrameFunc();
bool RenderFunc();

CKTVEngine::CKTVEngine(void) :
    m_pHGE(NULL),
    m_pSceneManager(NULL),
    m_pMachineInfo(NULL)
{
}

CKTVEngine::~CKTVEngine(void)
{
    if(m_pSceneManager) delete m_pSceneManager;
    if(m_pMachineInfo) delete m_pMachineInfo;
}

bool CKTVEngine::init()
{
    /** 创建渲染引擎HGE */
    m_pHGE = hgeCreate(HGE_VERSION);
    if(NULL == m_pHGE) return false;

    /** 读取配置 */
    m_pHGE->System_SetState(HGE_INIFILE, CONFIG_FILE);
    m_nWidth = m_pHGE->Ini_GetInt("display", "width", 1024);
    m_nHeight = m_pHGE->Ini_GetInt("display", "height", 768);
    m_nBPP = m_pHGE->Ini_GetInt("display", "bpp", 32);
    m_nFPS = m_pHGE->Ini_GetInt("display", "fps", 100);
    m_bWindowed = (bool)m_pHGE->Ini_GetInt("display", "windowed", 0);
    m_bCursor = (bool)m_pHGE->Ini_GetInt("display", "cursor", 0);
    m_szLogfile = m_pHGE->Ini_GetString("system", "logfile", "ktv.log");

    /** 配置HGE */
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

    /** SQL 链接 */
    strcpy(m_szDSNName, m_pHGE->Ini_GetString("database", "DSN", "ktv"));
    strcpy(m_szUsername, m_pHGE->Ini_GetString("database", "username", "sa"));
    strcpy(m_szPassword, m_pHGE->Ini_GetString("database", "password", ""));
    XModelConnection::Instance().Initialize(m_szDSNName, m_szUsername, m_szPassword);
    if(!XModelConnection::Instance().Connect()) return false;

    /** 包厢信息 */
    m_pMachineInfo = new CKTVMachineInfo();
    if(!m_pMachineInfo->SetMachineNo(m_pHGE->Ini_GetString("machine", "machineid", ""))) return false;
    else
    {
        m_pMachineInfo->StartListen();
        printf("欢迎进入 %s 包厢[%s]...\n", m_pMachineInfo->GetMachineInfo().MachineNo.c_str(), m_pMachineInfo->GetMachineInfo().m_TypeInfo.TypeName.c_str());
    }

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
    /** 判断时间是否到 */
    if(m_pMachineInfo->GetMinuteLeft() < 0)
    {
        /** DO STH. */
        printf("对不起，时间到...\n");

        return true;
    }

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
