#include <cstdio>
#include <wtypes.h>
#include <iostream>
#include <string>
#include "CommonClass.h"
using namespace std;

int main()
{
    XModelObject xmo("KTV", "sa", "");
    
    /** �������ݿ� */
    if(!xmo.Connect())
    {
        cout << xmo.GetLastError() << endl;
        return 0;
    }

    /** ��ѯ */
    XModelStream *XMS = xmo.Select("SELECT SongNo, SongName FROM Song");
    
    /** ��� */
    int sid;
    string songname;
    while(!XMS->eof())
    {
        (*XMS) >> sid >> songname;
        cout << sid << " " << songname << endl;
    }

    return 0;
}
