#include "CKTVRowMachine.h"

CKTVRowMachine::CKTVRowMachine(void)
{
}

CKTVRowMachine::~CKTVRowMachine(void)
{
}

XModelStream& CKTVRowMachine::operator << (XModelStream& s)
{
    for(int i = 0; i < 8; i++)
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

            case 7:
                {
                    string playlist;
                    s >> playlist;

                    XStringFunc str(playlist);
                    string arr[1024];
                    int count = str.Split("|", arr, 1024);

                    for(int i = 0; i < count; i++)
                    {
                        PlayListBak.push_back(str.ToInt(arr[i]));
                    }
                    PlayListCount = count;

                    break;
                }

            default: break;
            }
        }
    }

    return s;
}
