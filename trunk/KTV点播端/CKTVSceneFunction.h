#ifndef CKTVSCENEFUNCTION_H
#define CKTVSCENEFUNCTION_H
#pragma once
#include "global.h"
#include "cktvsceneobject.h"
#include "CKTVEngine.h"

class CKTVSceneFunction : public CKTVSceneObject
{
public:
    CKTVSceneFunction(void);
    virtual ~CKTVSceneFunction(void);

    virtual bool                        Init();
    virtual bool                        Update(float fDT);
    virtual bool                        Render(float fDT);

protected:
    SpritePair                          m_BG;

    float                               m_fBackTime;
};
#endif
