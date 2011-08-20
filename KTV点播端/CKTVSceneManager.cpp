#include "CKTVSceneManager.h"
using namespace std;

CKTVSceneManager::CKTVSceneManager(void) :
    m_pCurrentScene(NULL),
    m_pPrevScene(NULL),
    m_pNextScene(NULL)
{
}

CKTVSceneManager::~CKTVSceneManager(void)
{
}

bool CKTVSceneManager::Render(float fDT)
{
    if(m_pCurrentScene != NULL)
    {
        /** 获取状态 */
        CKTVSCENE_STATE state = m_pCurrentScene->GetState();

        switch(state)
        {
        case SCENE_COMING: return m_pCurrentScene->ComingRender(fDT); break;
        case SCENE_DISPLAYING: return m_pCurrentScene->Render(fDT); break;
        case SCENE_LEAVING: return m_pCurrentScene->LeavingRender(fDT); break;
        default: return false; break;
        }
    }

    return false;
}

bool CKTVSceneManager::Update(float fDT)
{
    /** 存在当前场景 */
    if(m_pCurrentScene != NULL)
    {
        /** 获取状态 */
        CKTVSCENE_STATE state = m_pCurrentScene->GetState();

        switch(state)
        {
        case SCENE_COMING: return m_pCurrentScene->ComingUpdate(fDT); break;
        case SCENE_DISPLAYING: return m_pCurrentScene->Update(fDT); break;
        case SCENE_LEAVING: return m_pCurrentScene->LeavingUpdate(fDT); break;
        case SCENE_LEFT:
            {
                delete m_pCurrentScene;
                m_pCurrentScene = m_pNextScene;
                m_pNextScene = NULL;

                if(m_pCurrentScene != NULL)
                {
                    m_pCurrentScene->SetState(SCENE_COMING);
                    return m_pCurrentScene->ComingUpdate(fDT);
                }
            }
        default: break;
        }
    }
    /** 不存在当前场景 */
    else
    {
        m_pCurrentScene = m_pNextScene;
        m_pNextScene = NULL;

        if(m_pCurrentScene != NULL)
        {
            m_pCurrentScene->Init();
            m_pCurrentScene->SetState(SCENE_COMING);
            return m_pCurrentScene->ComingUpdate(fDT);
        }
    }

    return false;
}

bool CKTVSceneManager::SetScene(char* szSceneName)
{
    /** 获取场景 */
    CKTVSceneObject* pObj = GetScene(szSceneName);
    if(pObj == NULL) return false;

    /** 设置下一个场景 */
    if(m_pNextScene != NULL)
    {
        delete m_pNextScene;
        m_pNextScene = NULL;
    }
    m_pNextScene = pObj;
    if(m_pCurrentScene != NULL)
    {
        m_pCurrentScene->SetState(SCENE_LEAVING);
    }

    return true;
}

CKTVSceneObject* CKTVSceneManager::GetScene(char* szSceneName)
{
    /** 创建场景 */
    CKTVSceneObject* pObj = SCENE_FACTORY.Create(szSceneName);
    
    /** 若创建失败 */
    if(NULL == pObj)
    {
        return NULL;
    }
    else
    {
        return pObj;
    }

    return NULL;
}
