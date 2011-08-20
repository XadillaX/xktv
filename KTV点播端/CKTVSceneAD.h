//////////////////////////////////////////////////////////////////////////
//
//	广告场景
//
//	Program by 死月(XadillaX) (admin@xcoder.in)
//  Create Date: 2011/08/20
//
//////////////////////////////////////////////////////////////////////////
#ifndef CKTVSCENE_H
#define CKTVSCENE_H
#pragma once
#include "cktvsceneobject.h"

#include "global.h"
#include "CKTVEngine.h"
#include <vector>
#include <hgesprite.h>
using namespace std;

typedef pair<HTEXTURE, hgeSprite*> SpritePair;

class CKTVSceneAD : public CKTVSceneObject
{
public:
    CKTVSceneAD(void);
    virtual ~CKTVSceneAD(void);

    virtual bool                        Init();
    virtual bool                        Update(float fDT);
    virtual bool                        Render(float fDT);

private:
    vector<SpritePair>                  m_Pic;
    int                                 m_nCurIdx;

    int                                 m_nCount;
    float                               m_fDelay;

    float                               m_fCurAlpha;
    bool                                m_bChanging;
};
#endif