#include "CKTVRowMachine.h"

CKTVRowMachine::CKTVRowMachine(void)
{
}

CKTVRowMachine::~CKTVRowMachine(void)
{
}

XModelStream& CKTVRowMachine::operator << (XModelStream& s)
{
    for(int i = 0; i < 7; i++)
    {
        if(IsCol(i))
        {
            switch(i)
            {
            case 0: s >> MachineNo; break;
            case 1: s >> Status; break;
            case 2: s >> StartTime; break;
            case 3: s >> ShutTime; break;
            case 4: s >> PlayNo; break;
            case 5: s >> ExpNo; break;
            case 6:
                {
                    s >> TypeNo;
                    
                    CKTVModelMachineType* pMMT = new CKTVModelMachineType();
                    pMMT->get_type_info(TypeNo, &m_TypeInfo);
                    delete pMMT;

                    break;
                }

            default: break;
            }
        }
    }

    return s;
}
