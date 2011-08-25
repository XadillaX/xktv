#ifndef XMODELOBJECT_H
#define XMODELOBJECT_H

#include <cstdarg>
#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include "Singleton.h"
#include "XModelQuery.h"
using namespace std;

#define OTL_ODBC_MSSQL_2005                 ///< Compile OTL 4/ODBC, MS SQL 2008
#define OTL_STL                             ///< Turn on STL features
#define OTL_ANSI_CPP                        ///< Turn on ANSI C++ typecasts
#include "otlv4.h"

typedef otl_datetime XDateTime;

/**
 * @brief 模型数据列基类
 * 继承以形成一个完整的数据列类，从数据流中获取数据或者向数据流中写入数据 
 *
 * @author XadillaX
 * @email admin@xcoder.in
 * @date 29-07-2011
 */
class XModelRowObject
{
public:
    XModelRowObject() { for(int i = 0; i < 256; i++) bCol[i] = true; }
    virtual ~XModelRowObject() {}

    void                                    ResetColumn() { memset(bCol, 0, sizeof(bCol)); }
    void                                    SetColumn(int count, ...)
    {
        ResetColumn();
        va_list arg_ptr;
        va_start(arg_ptr, count);
        for(int i = 0; i < count; i++)
        {
            int col = va_arg(arg_ptr, int);
            if(col < 256)
            {
                bCol[col] = true;
            }
        }
        va_end(arg_ptr);
    }
    bool                                    IsCol(int i) { return bCol[i]; }

    virtual XModelStream& operator <<       (XModelStream& s) { return s; };
    virtual XModelStream& operator >>       (XModelStream& s) { return s; };

protected:
    bool                                    bCol[256];
};

/**
 * @brief 模型单件连接对象
 * 为了保证数据库只有一个连接对象
 *
 * @author XadillaX
 * @email admin@xcoder.in
 * @date 29-07-2011
 */
class XModelConnection : public Singleton<XModelConnection>
{
public:
    XModelConnection() : m_bConnected(false), m_szLastError("") {};

public:
    void                             Initialize(const char* szDSN, const char* szUID, const char* pwd)
    {
        static bool bInited = false;
        if(!bInited)
        {
            otl_connect::otl_initialize();
            bInited = true;
        }

        /** ODBC连接字符串 */
        char szConnString[512];
        sprintf(szConnString, "uid=%s;pwd=%s;dsn=%s", szUID, pwd, szDSN);
        m_szConnString = szConnString;
    }

    bool                                    Connect(bool bConn = true)
    {
            if(bConn)
            {
                try
                {
                    /** 连接数据库 */
                    m_Connection.rlogon(m_szConnString.c_str());
                    m_bConnected = true;
                }
                catch(otl_exception& p)
                {
                    /** 获取失败信息 */
                    m_szLastError = (char*)p.msg;

                    return false;
                }
            }
            else
            {
                m_Connection.logoff();
                m_bConnected = false;
            }

            return true;
    }

    otl_connect&                            GetConnection() { return m_Connection; };
    string                                  GetLastError() { return m_szLastError; }

private:
    otl_connect                             m_Connection;
    string                                  m_szConnString;
    bool                                    m_bConnected;
    string                                  m_szLastError;
};

/**
 * @brief 模型类
 * M-V-C构架中的Model
 *
 * @author XadillaX
 * @email admin@xcoder.in
 * @date 29-07-2011
 */
class XModelObject
{
public:
    XModelObject();
    virtual ~XModelObject();

    string                                  GetPageSQL(string fields, string table, string condition, string order, int page, int pageSize);

    XModelStream*                           Select(const char* szSQL);
    bool                                    Query(const char* szSQL);

    string                                  GetLastError() { return m_szLastError; }

protected:
    string                                  m_szConnString;
    otl_connect*                            m_pConnection;
    XModelQuery                             m_XMQ;

    string                                  m_szLastSQL;
    string                                  m_szLastError;
};

#endif
