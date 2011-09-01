<%@ Page Language="C#" AutoEventWireup="true" CodeFile="MachineTypeList.aspx.cs" Inherits="backend_MachineTypeList" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>无标题页</title>
    
    <link type="text/css" href="../css/style.css" rel="Stylesheet" />
    <link type="text/css" href="../css/backend.css" rel="Stylesheet" />
</head>
<body>
    <form id="form1" runat="server">
    <div id="main-form">
        <table style="text-align: center;">
            <thead>
                <tr>
                    <td><b>类型编号</b> | </td>
                    <td><b>类型名称</b> | </td>
                    <td><b>价格(工作日白天|黄金|包夜|周末白天|黄金|包夜)</b> | </td>
                    <td><b>操作</b></td>
                </tr>
            </thead>
            
            <asp:Label ID="TableList" runat="server" Text=""></asp:Label>
        </table>
    </div>
    <div id="main-nav" style="text-align: center;"><asp:Button ID="NewType" runat="server" onclick="NewType_Click" Text="新建类型" /></div>
    </form>
</body>
</html>
