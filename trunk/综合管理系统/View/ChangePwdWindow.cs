using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using KTV.Controller;

namespace KTV.View
{
    public partial class ChangePwdWindow : Form
    {
        public ChangePwdWindow()
        {
            InitializeComponent();
        }

        private void Cancel_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void Modify_Click(object sender, EventArgs e)
        {
            String result = LoginCtrl.ChangePwd(Username.Text, Password.Text, NewPassword.Text, RePassword.Text);
            if (result != "")
            {
                MessageBox.Show(result, "错误", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            else
            {
                MessageBox.Show("修改成功！");
                Close();
            }
        }

        private void Username_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyValue == 13)
            {
                Modify_Click(sender, e);
            }
        }
    }
}
