#include <cstdio>
#include <wtypes.h>
#include <iostream>
#include <string>
#include "CommonClass.h"
using namespace std;

/** 使用模型流程：*/
/** 1. 新建XModelRowObject子类，代表一个模型的查询结果，其中包含每一列，并写好相应的>>\<<操作符函数。 */
/** 2. 新建XModelObject子类，代表某个模型，并派生通用查询函数，如get_information()等。 */

class songrow : public XModelRowObject
{
public:
    songrow() {};
    virtual ~songrow() {};

    virtual XModelStream& operator <<       (XModelStream& s)
    {
        if(IsCol(0)) s >> songid;
        if(IsCol(1)) s >> songname;
        if(IsCol(2)) s >> abc;

        return s;
    }

public:
    int songid;
    string songname;
    int abc;
};

class XSongModel : public XModelObject
{
public:
    XSongModel() {};
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
            buf[i++] << (*XMS);
        }

        return i;
    }
};

int main()
{
    /** 初始化连接对象并连接数据库 */
    XModelConnection::Instance().Initialize("KTV", "sa", "");
    if(!XModelConnection::Instance().Connect())
    {
        cout << XModelConnection::Instance().GetLastError() << endl;
        return 0;
    }

    XSongModel* xmo = new XSongModel();
    songrow row[256];
    int count = 0;
    count = xmo->get_song_info("", row);
    for(int i = 0; i < count; i++)
    {
        cout << row[i].songid << " " << row[i].songname << endl;
    }
    delete xmo;

    return 0;
}
