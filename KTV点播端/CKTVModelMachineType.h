//////////////////////////////////////////////////////////////////////////
//
//	KTV机器类型模型类
//
//	Program by 死月(XadillaX) (admin@xcoder.in)
//  Create Date: 2011/08/25
//
//////////////////////////////////////////////////////////////////////////
#ifndef CKTVMODELMACHINETYPE_H
#define CKTVMODELMACHINETYPE_H

#pragma once
#include "commonclass.h"
#include "cktvrowmachinetype.h"

class CKTVModelMachineType : public XModelObject
{
public:
    CKTVModelMachineType(void);
    virtual ~CKTVModelMachineType(void);

    bool                            get_type_info(string tid, CKTVRowMachineType* out);
};

#endif
