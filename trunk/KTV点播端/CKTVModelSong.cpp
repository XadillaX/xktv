#include "CKTVModelSong.h"

CKTVModelSong::CKTVModelSong(void)
{
}

CKTVModelSong::~CKTVModelSong(void)
{
}

int CKTVModelSong::get_song_by_artistno(int artistno, CKTVRowSong row[], int page, int pageSize)
{
    /** ��ѯ���� */
    string aquery = "SELECT ArtistName FROM Artist WHERE ArtistNo = " + XStringFunc::IntToString(artistno);
    string query = "ArtistNo = " + XStringFunc::IntToString(artistno);

    /** ��ȡ���� */
    XModelStream* AXMS = Select(aquery.c_str());
    string ArtistName = "";
    if(!AXMS->eof()) *AXMS >> ArtistName;

    XModelStream* XMS = Select(GetPageSQL("*", "Song", query, "SongNo DESC", page, pageSize).c_str());
    int i = 0;

    /** �ַ����� */
    while(!XMS->eof())
    {
        int RowNum;
        *XMS >> RowNum;

        row[i].SetColumn(9, 0, 1, 2, 3, 4, 5, 6, 7, 8);
        row[i++] << *XMS;

        row[i - 1].ArtistName = ArtistName;
    }

    return i;
}

int CKTVModelSong::get_song_group_count(int songno[], int count)
{
    string query = "SELECT COUNT(*) FROM Song WHERE SongNo IN(";
    for(int i = 0; i < count - 1; i++) query += (XStringFunc::IntToString(songno[i]) + ", ");
    query += (XStringFunc::IntToString(songno[count - 1])  + ")");

    XModelStream* XMS = Select(query.c_str());
    *XMS >> count;

    return count;
}

int CKTVModelSong::get_song_group(int songno[], int count, CKTVRowSong row[])
{
    string query = "SELECT * FROM Song WHERE SongNo IN(";
    for(int i = 0; i < count - 1; i++) query += (XStringFunc::IntToString(songno[i]) + ", ");
    query += (XStringFunc::IntToString(songno[count - 1])  + ")");

    XModelStream* XMS = Select(query.c_str());

    /** �ַ����� */
    int i = 0;
    while(!XMS->eof())
    {
        row[i].SetColumn(9, 0, 1, 2, 3, 4, 5, 6, 7, 8);
        row[i] << *XMS;
        i++;
    }

    /** �ָ�˳�� */
    for(int j = 0, k = 0; j < count; j++)
    {
        for(int l = j; l < i; l++)
        {
            if(songno[j] == row[l].SongNo)
            {
                CKTVRowSong tmp = row[l];
                row[l] = row[k];
                row[k] = tmp;
                k++;
                break;
            }
        }
    }
    
    XModelStream* AXMS;
    string aquery;

    for(int j = 0; j < i; j++)
    {        
        aquery = "SELECT ArtistName FROM Artist WHERE ArtistNo = " + XStringFunc::IntToString(row[j].ArtistNo);

        /** ��ȡ���� */
        AXMS = Select(aquery.c_str());
        row[j].ArtistName = "";
        if(!AXMS->eof()) *AXMS >> row[j].ArtistName;
    }
    return i;
}

int CKTVModelSong::get_song_by_pinyin(string pinyin, CKTVRowSong row[], int page, int pageSize)
{
    /** ��ѯ���� */
    string query = "SongPinyin LIKE '" + pinyin + "%'";

    XModelStream* XMS = Select(GetPageSQL("*", "Song", query, "SongNo DESC", page, pageSize).c_str());
    
    /** �ַ����� */
    int i = 0;
    while(!XMS->eof())
    {
        int RowNum;
        *XMS >> RowNum;

        row[i].SetColumn(9, 0, 1, 2, 3, 4, 5, 6, 7, 8);
        row[i] << *XMS;
        i++;
    }
    
    XModelStream* AXMS;
    string aquery;

    for(int j = 0; j < i; j++)
    {        
        aquery = "SELECT ArtistName FROM Artist WHERE ArtistNo = " + XStringFunc::IntToString(row[j].ArtistNo);

        /** ��ȡ���� */
        AXMS = Select(aquery.c_str());
        row[j].ArtistName = "";
        if(!AXMS->eof()) *AXMS >> row[j].ArtistName;
    }
    return i;
}

int CKTVModelSong::get_song_count_by_artistno(int artistno)
{
    string query = string("SELECT COUNT(*) FROM Song WHERE ArtistNo = ") + XStringFunc::IntToString(artistno);

    XModelStream* XMS = Select(query.c_str());

    int count;
    *XMS >> count;

    return count;
}

int CKTVModelSong::get_song_count_by_pinyin(string pinyin)
{
    string query = string("SELECT COUNT(*) FROM SONG WHERE SongPinyin LIKE '") + pinyin + ("%'");

    XModelStream* XMS = Select(query.c_str());

    int count;
    *XMS >> count;

    return count;
}

int CKTVModelSong::get_max_page_by_artistno(int artistno, int pageSize)
{
    int count = get_song_count_by_artistno(artistno);
    if(count == 0) return 1;

    int page = count / pageSize;
    if(count % pageSize == 0) return page;
    else return page + 1;
}

int CKTVModelSong::get_max_page_by_pinyin(string pinyin, int pageSize)
{
    int count = get_song_count_by_pinyin(pinyin);
    if(count == 0) return 1;

    int page = count / pageSize;
    if(count % pageSize == 0) return page;
    else return page + 1;
}

