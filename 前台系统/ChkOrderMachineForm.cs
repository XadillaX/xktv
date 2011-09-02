using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace 前台系统
{
    public partial class ChkOrderMachineForm : Form
    {
        SqlConnection conn;
        OrderData od;
        Model.ModelMachine MM;
        OrderMachineForm Parent;

        public ChkOrderMachineForm(SqlConnection _conn, OrderData _od, OrderMachineForm parent)
        {
            InitializeComponent();

            conn = _conn;
            od = _od;
            Parent = parent;

            MM = new 前台系统.Model.ModelMachine(conn);
        }

        private void Print_Click(object sender, EventArgs e)
        {
            bool flag = MM.OpenNewMachine(od);

            if (!flag)
            {
                MessageBox.Show("系统出错，请稍后再试。");
            }
            else
            {
                MessageBox.Show("操作成功！");
                Parent.Close();
                Close();
            }
        }

        private void ChkOrderMachineForm_Load(object sender, EventArgs e)
        {
            LMachineNo.Text = "包 厢 号: " + od.MachineNo;
            LMachineType.Text = "包厢类型: " + od.TypeName;
            LVIPNo.Text = "会员账号: " + od.VIPNo;
            LStartTime.Text = "开机时间: " + od.StartTime.ToString();
            LShutTime.Text = "关机时间: " + od.ShutTime.ToString();
            if (od.IsNight) LShutTime.Text += " (包夜)";
            LUseExp.Text = "使用积分: " + od.UseExp.ToString() + " 小时";
            LUseBalance.Text = "使用余额: " + od.UseBalance.ToString("0.00") + " 元";

            LMoney.Text = "应收金额: " + od.Money.ToString("0.00") + " 元";
            LMoneyFact.Text = "实收金额: " + od.MoneyFact.ToString("0.00") + " 元";
            LMoneyGiveBack.Text = "找    零: " + od.MoneyGiveBack.ToString("0.00") + " 元";

            LUsername.Text = "操 作 员: " + od.Username;
            LTime.Text = "操作时间: " + od.Time.ToString();
        }

        private void Cancel_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
