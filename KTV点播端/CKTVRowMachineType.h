//////////////////////////////////////////////////////////////////////////
//
//	KTV机器类型模型结果类
//
//	Program by 死月(XadillaX) (admin@xcoder.in)
//  Create Date: 2011/08/25
//
//////////////////////////////////////////////////////////////////////////
#ifndef CKTVROWMACHINETYPE_H
#define CKTVROWMACHINETYPE_H

#pragma once
#include "commonclass.h"

#define PRICE_WEEKDAYS_DAY              0
#define PRICE_WEEKDAYS_GOLD             1
#define PRICE_WEEKDAYS_NIGHT            2
#define PRICE_WEEKEND_DAY               3
#define PRICE_WEEKEND_GOLD              4
#define PRICE_WEEKEND_NIGHT             5

class CKTVRowMachineType : public XModelRowObject
{
public:
    CKTVRowMachineType(void);
    virtual ~CKTVRowMachineType(void);

    virtual XModelStream&               operator << (XModelStream& s);

public:
    string                              TypeNo;
    string                              TypeName;
    double                              Price[6];
};

#endif
