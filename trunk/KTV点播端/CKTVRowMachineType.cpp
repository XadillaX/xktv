#include "CKTVRowMachineType.h"

CKTVRowMachineType::CKTVRowMachineType(void)
{
}

CKTVRowMachineType::~CKTVRowMachineType(void)
{
}

XModelStream& CKTVRowMachineType::operator << (XModelStream& s)
{
    for(int i = 0; i < 3; i++)
    {
        if(IsCol(i))
        {
            switch(i)
            {
            case 0: s >> TypeNo; break;
            case 1: s >> TypeName; break;
            case 2:
                {
                    string szPrice;
                    s >> szPrice;

                    string szPriceArray[6];
                    XStringFunc xFunc(szPrice);
                    xFunc.Split("|", szPriceArray, 6);
                    xFunc.ToDouble(szPriceArray, Price, 6);
                }

            default: break;
            }
        }
    }

    return s;
}
