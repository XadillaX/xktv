#include "Model\XModelObject.h"

XModelObject::XModelObject(const char* szDNS, const char* szUID, const char* szPWD) :
    m_bConnected(false),
    m_szConnString(""),
    m_szLastError(""),
    m_szLastSQL("")
{
    otl_connect::otl_initialize();

    /** ODBC�����ַ��� */
    char szConnString[512];
    sprintf(szConnString, "uid=%s;pwd=%s;dsn=%s", szUID, szPWD, szDNS);
    m_szConnString = szConnString;
}

XModelObject::~XModelObject()
{
}

bool XModelObject::Connect(bool bConn)
{
    if(bConn)
    {
        try
        {
            /** �������ݿ� */
            m_Connection.rlogon(m_szConnString.c_str());
        }
        catch(otl_exception& p)
        {
            /** ��ȡʧ����Ϣ */
            m_szLastError = (char*)p.msg;

            return false;
        }
    }
    else
    {
        m_Connection.logoff();
    }

    return true;
}

XModelStream* XModelObject::Select(const char *szSQL)
{
    m_XMQ.Query(szSQL, &m_Connection);

    return m_XMQ.GetStream();
}

bool XModelObject::Query(const char* szSQL)
{
    m_XMQ.Query(szSQL, &m_Connection);

    return true;
}
