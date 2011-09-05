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
            sp = new SoundPlayer("Sound/Login.wav");
            sp.PlayLooping();
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
                //MessageBox.Show("登录成功！");
                LoginPanel.Visible = false;
                Functions.Visible = true;
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
    }
}
