#include "CKTVModelMachine.h"

CKTVModelMachine::CKTVModelMachine(void)
{
}

CKTVModelMachine::~CKTVModelMachine(void)
{
}

bool CKTVModelMachine::get_machine_info(string machineid, CKTVRowMachine* out)
{
    string query = "SELECT * FROM Machine WHERE MachineNo = '" + machineid + "'";

    XModelStream* XMS = Select(query.c_str());
    if(XMS->eof())
    {
        return false;
    }
    else
    {
        out->SetColumn(7, 0, 1, 2, 3, 4, 5, 6);
        *out << (*XMS);

        return true;
    }

    return true;
}
