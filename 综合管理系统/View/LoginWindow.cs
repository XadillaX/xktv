using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Media;
using KTV.Controller;

namespace KTV
{
    public partial class LoginWindow : Form
    {
        private SoundPlayer sp = null;

        public LoginWindow()
        {
            InitializeComponent();

            /** 载入声音文件 */
            //sp = new SoundPlayer("Sound/Login.wav");
            //sp.PlayLooping();
        }

        private void LoginBtn_Click(object sender, EventArgs e)
        {
            String result = LoginCtrl.Login(Username.Text, Password.Text, 1);

            if (result != "")
            {
                MessageBox.Show(result, "错误", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            else
            {
                LoginPanel.Visible = false;
                Functions.Visible = true;

                MainMenu.Visible = true;
            }
        }

        private void LoginWindow_Load(object sender, EventArgs e)
        {
            
        }

        private void CloseBtn_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void CloseBtn_Load(object sender, EventArgs e)
        {
            Username.Focus();
        }

        private void Username_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyValue == 13)
            {
                LoginBtn_Click(sender, e);
            }
        }

        private void ChangePwd_Click(object sender, EventArgs e)
        {
            View.ChangePwdWindow CPW = new KTV.View.ChangePwdWindow();
            CPW.ShowDialog();
        }

        private void 修改密码PToolStripMenuItem_Click(object sender, EventArgs e)
        {
            View.ChangePwdWindow CPW = new KTV.View.ChangePwdWindow();
            CPW.ShowDialog();
        }

        private void 用户ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            View.ViewUserWindow VUW = new KTV.View.ViewUserWindow();
            VUW.ShowDialog();
        }
    }
}
