#include "CKTVModelMachineType.h"

CKTVModelMachineType::CKTVModelMachineType(void)
{
}

CKTVModelMachineType::~CKTVModelMachineType(void)
{
}

bool CKTVModelMachineType::get_type_info(string tid, CKTVRowMachineType* out)
{
    string query = "SELECT * FROM MachineType WHERE TypeNo = '" + tid + "'";

    XModelStream* XMS = Select(query.c_str());
    if(XMS->eof())
    {
        return false;
    }
    else
    {
        out->SetColumn(3, 0, 1, 2);
        *out << (*XMS);

        return true;
    }

    return true;
}
