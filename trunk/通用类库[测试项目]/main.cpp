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
    /** ��ʼ�����Ӷ����������ݿ� */
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
