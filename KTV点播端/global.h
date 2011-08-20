//////////////////////////////////////////////////////////////////////////
//
//	ȫ���ļ�
//
//	Program by ����(XadillaX) (admin@xcoder.in)
//  Create Date: 2011/08/20
//
//////////////////////////////////////////////////////////////////////////
#ifndef GLOBAL_H
#define GLOBAL_H
#include <windows.h>
#include <wtypes.h>

#include <assert.h>
#include <hge.h>
#include <commonclass.h>

#include "singleton.h"
#include "objectfactory.h"

namespace global
{
    /** ������ */
#define KTV_TITLE                       "KTV�㲥ϵͳ"
#define CONFIG_FILE                     "ktv.ini"

    /** �򻯺� */
#define ENGINE                          (CKTVEngine::Instance())


extern HGE*                             g_pHGE;
};
#endif
