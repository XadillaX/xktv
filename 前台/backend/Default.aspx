<%@ Page Language="C#" AutoEventWireup="true"  CodeFile="Default.aspx.cs" Inherits="_Default" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>KTV后台管理系统</title>
    
    <link type="text/css" href="../css/style.css" rel="Stylesheet" />
    <link type="text/css" href="../css/backend.css" rel="Stylesheet" />
</head>
<body>
    <form id="form1" runat="server">
    <h1>KTV后台管理系统</h1>
    <hr />
    <div id="main-nav">
        <asp:Button ID="gotoMachineType" runat="server" Text="包厢类型" 
            onclick="gotoMachineType_Click" />
        <asp:Button ID="gotoMachine" runat="server" Text="包厢管理" />
    <hr />
    </div>
    
    <asp:Panel ID="FramePanel" runat="server">
        <asp:Label ID="Label1" runat="server"></asp:Label>
    </asp:Panel>
    
    </form>
</body>
</html>
