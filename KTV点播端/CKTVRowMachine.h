//////////////////////////////////////////////////////////////////////////
//
//	KTV机器结果嘞
//
//	Program by 死月(XadillaX) (admin@xcoder.in)
//  Create Date: 2011/08/25
//
//////////////////////////////////////////////////////////////////////////
#ifndef CKTVROWMACHINE_H
#define CKTVROWMACHINE_H

#pragma once
#include "commonclass.h"
#include "cktvmodelmachinetype.h"

class CKTVRowMachine : public XModelRowObject
{
public:
    CKTVRowMachine(void);
    virtual ~CKTVRowMachine(void);

    virtual XModelStream&           operator << (XModelStream& s);

public:
    string                          MachineNo;
    string                          Status;
    XDateTime                       StartTime;
    XDateTime                       ShutTime;
    int                             PlayNo;
    int                             ExpNo;
    string                          TypeNo;

    vector<int>                     PlayListBak;
    int                             PlayListCount;

    CKTVRowMachineType              m_TypeInfo;
};

#endif
