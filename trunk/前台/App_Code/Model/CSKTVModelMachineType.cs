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
///CSKTVModelMachineType 的摘要说明
/// </summary>
public class CSKTVModelMachineType : CSKTVModelObject
{
	public CSKTVModelMachineType()
	{
	}

    public bool AddType(String TypeNo, String TypeName, Double p1, Double p2, Double p3, Double p4, Double p5, Double p6)
    {
        String Price = p1.ToString() + "|" + p2.ToString() + "|" + p3.ToString() + "|" + p4.ToString() + "|" + p5.ToString() + "|" + p6.ToString();

        conn.Open();
        String query = "INSERT INTO MachineType(TypeNo, TypeName, Price) VALUES('" + TypeNo + "', '" + TypeName + "', '" + Price + "')";
        SqlCommand cmd = new SqlCommand(query, conn);
        int count = cmd.ExecuteNonQuery();

        conn.Close();
        return count != 0;
    }

    public SqlDataReader GetTypeListCloseByYourself()
    {
        conn.Open();
        SqlCommand cmd = new SqlCommand("SELECT * FROM MachineType", conn);

        return cmd.ExecuteReader();
    }
}
