<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Login.aspx.cs" Inherits="Login" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>用户登录</title>
    
    <link type="text/css" href="css/style.css" rel="Stylesheet" />
    <link type="text/css" href="css/login.css" rel="Stylesheet" />
</head>
<body>
    <form id="form1" runat="server">
    <div id="login-panel">
        <h1>KTV前台营业系统登录</h1>
        <asp:Label ID="Label1" runat="server" Text="用户名: "></asp:Label>
        <asp:TextBox ID="Username" runat="server"></asp:TextBox>
        <br />
        <asp:Label ID="Label2" runat="server" Text="密　码: "></asp:Label>
        <asp:TextBox ID="Password" runat="server" TextMode="Password"></asp:TextBox>
        <br />
        <asp:Button ID="LoginBtn" runat="server" Text="登录" onclick="LoginBtn_Click" />
        <br />
        <asp:Label ID="ErrMsg" runat="server" ForeColor="Red"></asp:Label>
        <br />
        <asp:Label ID="Label3" runat="server" CssClass="ar" 
            Text="作者: 宁波工程学院 计科091班 林莹莹"></asp:Label>
    </div>
    </form>
</body>
</html>
