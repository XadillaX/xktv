#include <cstdio>
#include <wtypes.h>
#include <iostream>
#include <string>
#include "CommonClass.h"
using namespace std;

/** ʹ��ģ�����̣�*/
/** 1. �½�XModelRowObject���࣬����һ��ģ�͵Ĳ�ѯ��������а���ÿһ�У���д����Ӧ��>>\<<������������ */
/** 2. �½�XModelObject���࣬����ĳ��ģ�ͣ�������ͨ�ò�ѯ��������get_information()�ȡ� */

class songrow : public XModelRowObject
{
public:
    songrow() {};
    virtual ~songrow() {};

public:
    int songid;
    string songname;
    int abc;
};

XModelStream& operator >> (XModelStream& s, songrow& row)
{
    if(row.IsCol(0)) s >> row.songid;
    if(row.IsCol(1)) s >> row.songname;
    if(row.IsCol(2)) s >> row.abc;

    return s;
}

class XSongModel : public XModelObject
{
public:
    XSongModel(string a, string b, string c) : XModelObject(a.c_str(), b.c_str(), c.c_str()) {};
    virtual ~XSongModel() {};

public:
    int get_song_info(const char* condition, songrow buf[])
    {
        string query = "SELECT SongNo, SongName FROM Song";
        if(strlen(condition) != 0)
        {
            query += " WHERE ";
            query += condition;
        }

        XModelStream* XMS = Select(query.c_str());
        int i = 0;
        while(!XMS->eof())
        {
            buf[i].SetColumn(2, 0, 1);
            (*XMS) >> buf[i++];
        }

        return i;
    }
};

int main()
{
    XSongModel xmo("KTV", "sa", "");
    
    /** �������ݿ� */
    if(!xmo.Connect())
    {
        cout << xmo.GetLastError() << endl;
        return 0;
    }
    
    /** ��� */
    songrow row[256];
    int count;
    count = xmo.get_song_info("", row);
    for(int i = 0; i < count; i++)
    {
        cout << row[i].songid << " " << row[i].songname << endl;
    }

    return 0;
}
