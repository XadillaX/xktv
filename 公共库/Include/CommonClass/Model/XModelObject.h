#ifndef XMODELOBJECT_H
#define XMODELOBJECT_H

#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include "XModelQuery.h"
using namespace std;

#define OTL_ODBC_MSSQL_2005                 ///< Compile OTL 4/ODBC, MS SQL 2008
#define OTL_STL                             ///< Turn on STL features
#define OTL_ANSI_CPP                        ///< Turn on ANSI C++ typecasts
#include "otlv4.h"

class XModelObject
{
public:
    XModelObject(const char* szDNS, const char* szUID, const char* szPWD);
    virtual ~XModelObject();

    bool                                    Connect(bool bConn = true);

    XModelStream*                           Select(const char* szSQL);
    bool                                    Query(const char* szSQL);

    string                                  GetLastError() { return m_szLastError; }

protected:
    string                                  m_szConnString;
    otl_connect                             m_Connection;

    bool                                    m_bConnected;
    XModelQuery                             m_XMQ;

    string                                  m_szLastSQL;
    string                                  m_szLastError;
};

#endif
