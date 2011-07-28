#include "Model\XModelObject.h"

XModelObject::XModelObject()
{
    m_pConnection = &(XModelConnection::Instance().GetConnection());
}

XModelObject::~XModelObject()
{
}

XModelStream* XModelObject::Select(const char *szSQL)
{
    m_XMQ.Query(szSQL, m_pConnection);

    return m_XMQ.GetStream();
}

bool XModelObject::Query(const char* szSQL)
{
    m_XMQ.Query(szSQL, m_pConnection);

    return true;
}
