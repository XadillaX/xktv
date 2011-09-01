using System;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Xml.Linq;
using System.Data.SqlClient;

public partial class _Default : System.Web.UI.Page 
{
    protected SqlConnection conn;
    protected CSKTVModelUser UserModel;

    protected void CheckLogin()
    {
        if (!UserModel.IsLogined(Convert.ToInt32(Session["uid"]), (String)Session["username"]))
        {
            Response.Redirect("Login.aspx");

            return;
        }
    }

    protected void CreateModel()
    {
        /* 连接对象 */
        conn = new SqlConnection(ConfigurationManager.ConnectionStrings["con"].ConnectionString);

        /** 用户模型 */
        UserModel = new CSKTVModelUser();
        UserModel.BindConnection(conn);
    }

    protected void Page_Load(object sender, EventArgs e)
    {
        CreateModel();
        CheckLogin();
    }
}
