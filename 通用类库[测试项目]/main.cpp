#include <cstdio>
#include <wtypes.h>
#include <iostream>
#include <string>
#include "CommonClass.h"
using namespace std;

int main()
{
    XModelObject xmo("KTV", "sa", "");
    
    /** 连接数据库 */
    if(!xmo.Connect())
    {
        cout << xmo.GetLastError() << endl;
        return 0;
    }

    /** 查询 */
    XModelStream *XMS = xmo.Select("SELECT SongNo, SongName FROM Song");
    
    /** 结果 */
    int sid;
    string songname;
    while(!XMS->eof())
    {
        (*XMS) >> sid >> songname;
        cout << sid << " " << songname << endl;
    }

    return 0;
}
