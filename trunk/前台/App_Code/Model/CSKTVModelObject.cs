using System;
using System.Data;
using System.Configuration;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Xml.Linq;
using System.Data.SqlClient;

/// <summary>
///CSKTVModelObject 的摘要说明
/// </summary>
public class CSKTVModelObject
{
    protected SqlConnection conn;
    protected bool bConnected = false;

	public CSKTVModelObject()
	{
	}

    /** 绑定链接对象 */
    public void BindConnection(SqlConnection _conn)
    {
        conn = _conn;
        bConnected = true;
    }

    public bool IsBind()
    {
        return bConnected;
    }

    public String GetPaginationString(string fields, string table, string condition, string order, int page, int pageSize)
    {
        string rst = "SELECT ROW_NUMBER() OVER ";
        if(order != "")
        {
            rst += ("(ORDER BY " + order + ") ");
        }
        rst += ("AS RowNumber, " + fields + (" FROM ") + table);
        if(condition != "")
        {
            rst += (" WHERE " + condition);
        }

        string n1, n2;
        n1 = pageSize.ToString();
        n2 = (pageSize * (page - 1)).ToString();

        string rtn = "SELECT TOP ";
        rtn += n1;
        rtn += " ";
        rtn += (fields + "\nFROM\n    (\n    ");
        rtn += (rst + "\n    ) A\nWHERE RowNumber > ");
        rtn += n2;

        return rtn;
    }
}
