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

public partial class backend_AddMachineType : System.Web.UI.Page
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

        /* 包厢类型 */
        MachineTypeModel = new CSKTVModelMachineType();
        MachineTypeModel.BindConnection(conn);
    }

    protected void Page_Load(object sender, EventArgs e)
    {
        CreateModel();
        CheckLogin();
    }
    protected void Add_Click(object sender, EventArgs e)
    {
        if (TypeNo.Text.Length != 5)
        {
            ErrMsg.Text = "类型编号长度需为5。";
            return;
        }

        if (TypeName.Text.Length < 1 || TypeName.Text.Length > 10)
        {
            ErrMsg.Text = "喂！(#`O′)  类型名需在1~10位之间。";
            return;
        }

        String []price = new String[6];
        Double []fPrice = new Double[6];
        price[0] = Price1.Text; price[1] = Price2.Text; price[2] = Price3.Text;
        price[3] = Price4.Text; price[4] = Price5.Text; price[5] = Price6.Text;
        for (int i = 0; i < 6; i++)
        {
            fPrice[i] = Convert.ToDouble(price[i]);
        }

        if(!MachineTypeModel.AddType(TypeNo.Text, TypeName.Text, fPrice[0], fPrice[1], fPrice[2], fPrice[3], fPrice[4], fPrice[5]))
        {
            ErrMsg.Text = "系统错误，请重试。";
            return;
        }

        Response.Redirect("MachineTypeList.aspx");
    }
    protected void BackBtn_Click(object sender, EventArgs e)
    {
        Response.Redirect("MachineTypeList.aspx");
    }
}
