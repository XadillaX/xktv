using System;
using System.Collections;
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

public partial class Login : System.Web.UI.Page
{
    CSKTVModelUser UserModel;
    SqlConnection conn;

    protected void CreateModel()
    {
        /* 连接对象 */
        conn = new SqlConnection(ConfigurationManager.ConnectionStrings["con"].ConnectionString);

        /* 用户模型 */
        UserModel = new CSKTVModelUser();
        UserModel.BindConnection(conn);
    }

    protected void Page_Load(object sender, EventArgs e)
    {
        CreateModel();
    }

    protected void LoginBtn_Click(object sender, EventArgs e)
    {
        /* 检查登录 */
        if (UserModel.ChkLogin(Username.Text, Password.Text))
        {
            /** 记录SESSION */
            Session["username"] = UserModel.GetUsername();
            Session["uid"] = UserModel.GetUID();

            /** 返回 */
            Response.Redirect("Default.aspx");
            return;
        }
        else
        {
            ErrMsg.Text = "错误的用户名或者密码，或者系统错误。";
            return;
        }
    }
}
