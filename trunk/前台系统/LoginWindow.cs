using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Data.SqlClient;
using 前台系统.Model;

namespace 前台系统
{
    public partial class LoginWindow : Form
    {
        SqlConnection conn;
        ModelUser MU;

        MainWindow MW;

        public LoginWindow()
        {
            InitializeComponent();

            // 连接对象
            try
            {
                conn = new SqlConnection("Server=localhost;DataBase=ktv;Uid=sa;pwd=;");
            }
            catch(Exception e)
            {
                MessageBox.Show("数据库连接错误！");
                Close();
            }

            MU = new ModelUser(conn);
        }

        private void Username_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyValue == 13)
            {
                Login();
            }
        }

        private void Login()
        {
            ErrMsg.Text = "正在登录...";
            ErrMsg.Update();

            int UID = MU.Login(Username.Text, Password.Text, 0);

            switch (UID)
            {
            case -1:
                {
                    ErrMsg.Text = "用户名或者密码错误...";
                    break;
                }

            case -2:
                {
                    ErrMsg.Text = "权限不足...";
                    break;
                }

            default:
                {
                    ErrMsg.Text = "登录成功...";
                    MW = new MainWindow(UID, Username.Text, conn);
                    
                    MW.Show();
                    Hide();

                    break;
                }
            }

            return;
        }

        private void Password_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyValue == 13)
            {
                Login();
            }
        }

        private void LoginBtn_Click(object sender, EventArgs e)
        {
            Login();
        }
    }
}
