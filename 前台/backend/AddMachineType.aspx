<%@ Page Language="C#" AutoEventWireup="true" CodeFile="AddMachineType.aspx.cs" Inherits="backend_AddMachineType" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>无标题页</title>
    
    <link type="text/css" href="../css/style.css" rel="Stylesheet" />
    <link type="text/css" href="../css/backend.css" rel="Stylesheet" />
    <style type="text/css">
        .style1
        {
            text-align: center;
        }
        .style2
        {
            color: #FF3300;
            text-align: center;
        }
        .style3
        {
            text-align: left;
        }
        .style4
        {
            height: 26px;
        }
    </style>
</head>
<body>
    <form id="form1" runat="server">
    <div id="main-form" class="style1">
        <div class="style1">
        <span class="style2">新增包厢类型</span></div>
        <table style="width:100%;">
            <tr>
                <td style="text-align: right">
                    类型编号</td>
                <td style="text-align: left" colspan="2">
                    <asp:TextBox ID="TypeNo" runat="server" Width="211px"></asp:TextBox>
                </td>
                <td class="style3">
                    长度规定为5位。</td>
            </tr>
            <tr>
                <td style="text-align: right">
                    类型名称</td>
                <td style="text-align: left" colspan="2">
                    <asp:TextBox ID="TypeName" runat="server" Width="211px"></asp:TextBox>
                </td>
                <td style="text-align: left">
                    长度最多为10位。</td>
            </tr>
            <tr>
                <td colspan="4">
                    &nbsp;</td>
            </tr>
            <tr>
                <td>
                    价格</td>
                <td>
                    白天</td>
                <td>
                    黄金时段</td>
                <td>
                    包夜</td>
            </tr>
            <tr>
                <td class="style4">
                    工作日</td>
                <td class="style4">
                    <asp:TextBox ID="Price1" runat="server" Width="125px"></asp:TextBox>
                </td>
                <td class="style4">
                    <asp:TextBox ID="Price2" runat="server" Width="125px"></asp:TextBox>
                </td>
                <td class="style4">
                    <asp:TextBox ID="Price3" runat="server" Width="125px"></asp:TextBox>
                </td>
            </tr>
            <tr>
                <td>
                    周末</td>
                <td>
                    <asp:TextBox ID="Price4" runat="server" Width="125px"></asp:TextBox>
                </td>
                <td>
                    <asp:TextBox ID="Price5" runat="server" Width="125px"></asp:TextBox>
                </td>
                <td>
                    <asp:TextBox ID="Price6" runat="server" Height="22px" Width="125px"></asp:TextBox>
                </td>
            </tr>
        </table>
        <div id="main-nav"><asp:Button ID="Add" runat="server" onclick="Add_Click" Text="新增" />
            <asp:Button ID="BackBtn" runat="server" onclick="BackBtn_Click" Text="返回" />
        </div>
        <br />
        <asp:Label ID="ErrMsg" runat="server" ForeColor="#FF3300"></asp:Label>
    </div>
    </form>
</body>
</html>
