using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using 前台系统.Model;
using System.Data.SqlClient;

namespace 前台系统.Windows
{
    public partial class RegForm : Form
    {
        SqlConnection Conn;
        ModelVIP MV;

        public RegForm(SqlConnection _Conn)
        {
            InitializeComponent();

            Conn = _Conn;
            MV = new ModelVIP(Conn);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            String result = MV.RegVIP(VIPNo.Text, VIPName.Text, VIPID.Text, VIPMobile.Text, Convert.ToDouble(Balance.Value));
            if ("" == result)
            {
                MessageBox.Show("注册成功！");
                Close();
                return;
            }
            else
            {
                MessageBox.Show("注册失败: " + result);
                return;
            }
        }
    }
}
