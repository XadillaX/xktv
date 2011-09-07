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
                ShowLogin();
            }
        }

        private int Login(String username, String password)
        {
            int UID = MU.Login(Username.Text, Password.Text, 0);

            return UID;
        }

        private void ShowLogin()
        {
            ErrMsg.Text = "正在登录...";
            ErrMsg.Update();

            int rst = Login(Username.Text, Password.Text);

            switch (rst)
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
                    MW = new MainWindow(rst, Username.Text, conn);

                    MW.Show();
                    Hide();

                    break;
                }
            }
        }

        private void Password_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyValue == 13)
            {
                ShowLogin();
            }
        }

        private void LoginBtn_Click(object sender, EventArgs e)
        {
            ShowLogin();
        }
    }
}
