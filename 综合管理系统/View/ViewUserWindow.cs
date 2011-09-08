using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using KTV.Model.DataRow;
using KTV.Model.DataLink;
using KTV.Controller;

namespace KTV.View
{
    public partial class ViewUserWindow : Form
    {
        IList<FrontDeskUserInfo> list;
        int EditIdx = -1;
        bool bAdd;

        public ViewUserWindow(bool isAdd)
        {
            InitializeComponent();

            /** 是否添加模式 */
            bAdd = isAdd;
        }

        private void ViewUserWindow_Load(object sender, EventArgs e)
        {
            //FrontDeskUserModel FDUM = new FrontDeskUserModel();
            //list = FDUM.GetUserInfo("", true);
            list = UserCtrl.GetUserList("");

            for (int i = 0; i < list.Count(); i++)
            {
                frontDeskUserInfoBindingSource.Add(list[i]);
            }

            if (bAdd)
            {
                Username.Enabled = true;
                Modify.Text = "添加(&A)";
                Delete.Visible = false;
            }
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            if (bAdd) return;
            if (-1 == e.RowIndex) return;

            if (EditIdx != e.RowIndex && EditIdx != -1)
            {
                if (Password.Text != "" || isAdmin.Checked != Convert.ToBoolean(list[EditIdx].Type))
                {
                    if (MessageBox.Show("内容发生改变，确定放弃？", "消息", MessageBoxButtons.YesNo) == DialogResult.No)
                    {
                        return;
                    }
                }
            }

            EditIdx = e.RowIndex;
            Username.Text = list[EditIdx].Username;
            Password.Text = "";
            isAdmin.Checked = Convert.ToBoolean(list[EditIdx].Type);
        }

        private void Modify_Click(object sender, EventArgs e)
        {
            if (bAdd)
            {
                String result = UserCtrl.CreateUser(Username.Text, Password.Text, isAdmin.Checked);
                if ("" != result)
                {
                    MessageBox.Show(result, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                else
                {
                    IList<FrontDeskUserInfo> tmp = UserCtrl.GetUserList("Username = '" + Username.Text + "'");
                    frontDeskUserInfoBindingSource.Add(tmp[0]);
                    list.Add(tmp[0]);

                    MessageBox.Show("添加成功！");
                    return;
                }
            }
            else
            {
                if (EditIdx == -1)
                {
                    MessageBox.Show("未选中任何数据！", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                String result = UserCtrl.ModifyUser(Username.Text, Password.Text, isAdmin.Checked);
                if ("" != result)
                {
                    MessageBox.Show(result, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
                else
                {
                    IList<FrontDeskUserInfo> tmp = UserCtrl.GetUserList("Username = '" + Username.Text + "'");
                    frontDeskUserInfoBindingSource[EditIdx] = tmp[0];
                    list[EditIdx] = tmp[0];

                    MessageBox.Show("修改成功！");
                    return;
                }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void Username_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyValue == 13)
            {
                Modify_Click(sender, e);
            }
        }

        private void Delete_Click(object sender, EventArgs e)
        {
            if (-1 == EditIdx)
            {
                MessageBox.Show("没有选中任何用户！", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            if (MessageBox.Show("确定删除？", "消息", MessageBoxButtons.OKCancel, MessageBoxIcon.Question) == DialogResult.Cancel)
            {
                return;
            }

            String result = UserCtrl.DeleteUser(list[EditIdx].UID);
            if ("" != result)
            {
                MessageBox.Show(result, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            else
            {
                frontDeskUserInfoBindingSource.RemoveAt(EditIdx);
                list.RemoveAt(EditIdx);
                Username.Text = "";
                Password.Text = "";
                isAdmin.Checked = false;
                EditIdx = -1;

                MessageBox.Show("删除成功！");
                return;
            }
        }
    }
}
