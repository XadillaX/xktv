#include "Model\XModelObject.h"

XModelObject::XModelObject()
{
    m_pConnection = &(XModelConnection::Instance().GetConnection());
}

XModelObject::~XModelObject()
{
}

string XModelObject::GetPageSQL(string fields, string table, string condition, string order, int page, int pageSize)
{
    string rst = "SELECT ROW_NUMBER() OVER ";
    if(order != "")
    {
        rst += (string("(ORDER BY ") + order + string(") "));
    }
    rst += (string("AS RowNumber, ") + fields + (" FROM ") + table);
    if(condition != "")
    {
        rst += (" WHERE " + condition);
    }

    char n1[16], n2[16];
    itoa(pageSize, n1, 10);
    itoa(pageSize * (page - 1), n2, 10);

    string rtn = "SELECT TOP ";
    rtn += n1;
    rtn += " ";
    rtn += (fields + "\nFROM\n    (\n    ");
    rtn += (rst + "\n    ) A\nWHERE RowNumber > ");
    rtn += n2;

    return rtn;
}

XModelStream* XModelObject::Select(const char *szSQL)
{
    try{
        m_XMQ.Query(szSQL, m_pConnection);
    }
    catch(otl_exception& p){        // intercept OTL exceptions
        cerr<<p.msg<<endl;          // print out error message
        cerr<<p.code<<endl;         // print out error code
        cerr<<p.var_info<<endl;     // print out the variable that caused the error
        cerr<<p.sqlstate<<endl;     // print out SQLSTATE message
        cerr<<p.stm_text<<endl;     // print out SQL that caused the 

        return NULL;
    }

    return m_XMQ.GetStream();
}

bool XModelObject::Query(const char* szSQL)
{
    try{
        m_XMQ.Query(szSQL, m_pConnection);
    }
    catch(otl_exception& p){        // intercept OTL exceptions
        cerr<<p.msg<<endl;          // print out error message
        cerr<<p.code<<endl;         // print out error code
        cerr<<p.var_info<<endl;     // print out the variable that caused the error
        cerr<<p.sqlstate<<endl;     // print out SQLSTATE message
        cerr<<p.stm_text<<endl;     // print out SQL that caused the error

        return false;
    }

    return true;
}
