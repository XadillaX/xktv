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

enum USER_TYPE
{
    UT_FRONTEND = 0,
    UT_BACKEND = 1
};

/// <summary>
///CSKTVModelUser 的摘要说明
/// </summary>
public class CSKTVModelUser : CSKTVModelObject
{
    private int UID;
    private String Username;
    private USER_TYPE UserType;

    public String GetUsername() { return Username; }
    public int GetUID() { return UID; }
    public int GetUserType() { return (int)UserType; }

	public CSKTVModelUser()
	{
	}

    public bool IsLogined(int _UID, String username)
    {
        /* 用户名为空 */
        if (username == null || _UID == null)
        {
            return false;
        }
        conn.Open();

        /* 查询命令 */
        String query = "SELECT * FROM FrontDeskUser WHERE Username = '" + username + "' AND UID = " + _UID.ToString();
        SqlCommand cmd = new SqlCommand(query, conn);
        SqlDataReader dr = cmd.ExecuteReader();

        /* 查询 */
        bool rst = dr.Read();

        if(rst)
        {
            Username = username;
            UID = _UID;
            UserType = (USER_TYPE)Convert.ToInt32(dr["Type"]);
        }

        dr.Close();
        conn.Close();
        
        return rst;
    }

    public bool ChkLogin(String username, String password)
    {
        conn.Open();
        String query = "SELECT * FROM FrontDeskUser WHERE Username = '" + username + "' AND Password = '" + password + "'";
        SqlCommand cmd = new SqlCommand(query, conn);
        
        SqlDataReader dr = cmd.ExecuteReader();

        bool rst = dr.Read();
        if (!rst)
        {
            dr.Close();
            conn.Close();
            return false;
        }

        UID = Convert.ToInt32(dr["UID"]);
        Username = dr["Username"].ToString();
        UserType = (USER_TYPE)Convert.ToInt32(dr["Type"]);

        query = "UPDATE FrontDeskUser SET LoginTime = '" + DateTime.Now.ToString() + "' WHERE UID = " + dr["UID"].ToString();
        dr.Close();
        cmd.CommandText = query;
        int count = cmd.ExecuteNonQuery();
        if (count == 0)
        {
            conn.Close();
            return false;
        }

        conn.Close();
        return true;
    }
}
