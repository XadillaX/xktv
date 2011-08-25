#ifndef XMODELQUERY_H
#define XMODELQUERY_h

#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <map>
#include <list>
using namespace std;

#define OTL_ODBC_MSSQL_2005                 ///< Compile OTL 4/ODBC, MS SQL 2008
#define OTL_STL                             ///< Turn on STL features
#define OTL_ANSI_CPP                        ///< Turn on ANSI C++ typecasts

#include "otlv4.h"
#define SAFEDEL(p)                          if(p != NULL) { delete p; p = NULL; }

#define toInt                               atoi
#define toDouble                            atof

typedef otl_stream                          XModelStream;
typedef otl_long_string                     XModelText;

/**
 * @brief 模型查询对象
 * 模型查询对象
 *
 * @author XadillaX
 * @email admin@xcoder.in
 * @date 29-07-2011
 */
class XModelQuery
{
public:
    XModelQuery();
    virtual ~XModelQuery();

    void                                    Query(const char* szSQL, otl_connect *db, int nBufferSize = 1);
    XModelStream*                           GetStream()
    {
        if(m_bQueried) return m_pStream;
        else return NULL;
    }

protected:
    bool                                    m_bQueried;

    XModelStream*                           m_pStream;
};

#endif
