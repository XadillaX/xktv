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

public partial class backend_MachineTypeList : System.Web.UI.Page
{
    CSKTVModelUser UserModel;
    CSKTVModelMachineType MachineTypeModel;

    SqlConnection conn;

    protected void CheckLogin()
    {
        if (!UserModel.IsLogined(Convert.ToInt32(Session["uid"]), (String)Session["username"]))
        {
            Response.Redirect("../Login.aspx");
            return;
        }

        /* 权限不够 */
        if (UserModel.GetUserType() == 0)
        {
            Response.Redirect("../Default.aspx");
            return;
        }
    }

    protected void CreateModel()
    {
        /* 连接对象 */
        conn = new SqlConnection(ConfigurationManager.ConnectionStrings["con"].ConnectionString);

        /* 用户模型 */
        UserModel = new CSKTVModelUser();
        UserModel.BindConnection(conn);

        /* 机器类型模型 */
        MachineTypeModel = new CSKTVModelMachineType();
        MachineTypeModel.BindConnection(conn);
    }

    protected void Page_Load(object sender, EventArgs e)
    {
        CreateModel();
        CheckLogin();

        String html = "";
        SqlDataReader List = MachineTypeModel.GetTypeListCloseByYourself();
        while (List.Read())
        {
            html += "<tr style='text-align: center;'>";
            html += ("<td>" + List["TypeNo"] + "</td>");
            html += ("<td>" + List["TypeName"] + "</td>");
            html += ("<td>" + List["Price"] + "</td>");
            html += ("<td>修改 / 删除</td>");
            html += "</tr>";
        }

        TableList.Text = html;
    }
    protected void NewType_Click(object sender, EventArgs e)
    {
        Response.Redirect("AddMachineType.aspx");
    }
}
