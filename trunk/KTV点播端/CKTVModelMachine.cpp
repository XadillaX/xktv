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
        out->SetColumn(8, 0, 1, 2, 3, 4, 5, 6, 7);
        *out << (*XMS);

        return true;
    }

    return true;
}

void CKTVModelMachine::back_machine_play_list(string machineid, CKTVRowSong row[], int count)
{
    string playlist = "";
    for(int i = 0; i < count; i++)
    {
        playlist += (XStringFunc::IntToString(row[i].SongNo) + "|");
    }

    string query = "UPDATE Machine SET PlayListText='" + playlist + "' WHERE MachineNo='" + machineid + "'";
    XModelStream* XMS = Select(query.c_str());
    XMS->close();
}
