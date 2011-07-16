#include "Model\XModelQuery.h"

XModelQuery::XModelQuery() :
    m_pStream(NULL),
    m_bQueried(false)
{
}

XModelQuery::~XModelQuery()
{
    SAFEDEL(m_pStream);
}

void XModelQuery::Query(const char* szSQL, otl_connect *db, int nBufferSize)
{
    /** É¾³ýÏÈÇ°STREAM */
    SAFEDEL(m_pStream);
    
    m_pStream = new XModelStream(nBufferSize, szSQL, *db);
    m_bQueried = true;
}
