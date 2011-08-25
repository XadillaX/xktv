//////////////////////////////////////////////////////////////////////////
//
//	KTV机器模型类
//
//	Program by 死月(XadillaX) (admin@xcoder.in)
//  Create Date: 2011/08/25
//
//////////////////////////////////////////////////////////////////////////
#ifndef CKTVMODELMACHINE_H
#define CKTVMODELMACHINE_H

#pragma once
#include "commonclass.h"
#include "cktvrowmachine.h"

class CKTVModelMachine : public XModelObject
{
public:
    CKTVModelMachine(void);
    virtual ~CKTVModelMachine(void);

    bool                            get_machine_info(string machineid, CKTVRowMachine* out);
};

#endif
