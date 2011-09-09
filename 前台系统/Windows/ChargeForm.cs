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
    public partial class ChargeForm : Form
    {
        private SqlConnection Conn;
        private Model.ModelVIP MV;

        public ChargeForm(SqlConnection _Conn)
        {
            InitializeComponent();

            Conn = _Conn;
            MV = new 前台系统.Model.ModelVIP(Conn);
        }

        private void OK_Click(object sender, EventArgs e)
        {
            Dictionary<String, String> list;
            list = MV.GetVIPInfo(VIPNo.Text);

            if (null == list)
            {
                MessageBox.Show("不存在的VIP用户！");
                return;
            }

            bool result = MV.ChangeBalance(VIPNo.Text, Convert.ToDouble(Money.Value));
            if (result)
            {
                MessageBox.Show("充值成功！");
            }
            else MessageBox.Show("充值失败！");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
