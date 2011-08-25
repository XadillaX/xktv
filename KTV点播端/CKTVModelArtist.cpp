#include "CKTVModelArtist.h"

CKTVModelArtist::CKTVModelArtist(void)
{
}

CKTVModelArtist::~CKTVModelArtist(void)
{
}

bool CKTVModelArtist::get_artist_info(int ArtistNo, CKTVRowArtist* out)
{
    string query = "SELECT * FROM Artist WHERE ArtistNo = " + XStringFunc::IntToString(ArtistNo);

    XModelStream* XMS = Select(query.c_str());
    if(XMS->eof())
    {
        return false;
    }
    else
    {
        out->SetColumn(6, 0, 1, 2, 3, 4, 5);
        *out << (*XMS);

        return true;
    }
}

int CKTVModelArtist::get_artist_info_by_pinyin(string pinyin, CKTVRowArtist row[], int page, int pageSize)
{
    /** 查询条件 ArtistPinyin LIKE '拼音%' */
    string query = "ArtistPinyin LIKE '";
    query += pinyin;
    query += "%'";

    /** 分页SQL */
    char buf[1024];
    strcpy(buf, this->GetPageSQL("*", "Artist", query, "ArtistName ASC", page, pageSize).c_str());

    /** 获取数据 */
    XModelStream* XMS = Select(buf);
    int i = 0;

    /** 分发数据 */
    while(!XMS->eof())
    {
        int RowNum;
        *XMS >> RowNum;

        row[i].SetColumn(6, 0, 1, 2, 3, 4, 5);
        row[i++] << *XMS;
    }

    return i;
}

int CKTVModelArtist::get_artist_count_by_pinyin(string pinyin)
{
    string query = string("SELECT COUNT(*) FROM Artist WHERE ArtistPinyin LIKE '") + pinyin + ("%'");

    XModelStream* XMS = Select(query.c_str());

    int count;
    *XMS >> count;

    return count;
}

int CKTVModelArtist::get_max_page_by_pinyin(string pinyin, int pageSize)
{
    int count = get_artist_count_by_pinyin(pinyin);
    if(count == 0) return 1;

    int page = count / pageSize;
    if(count % pageSize == 0) return page;
    else return page + 1;
}
