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

namespace KTV.View
{
    public partial class ViewUserWindow : Form
    {
        IList<FrontDeskUserInfo> list;
        int EditIdx = -1;

        public ViewUserWindow()
        {
            InitializeComponent();
        }

        private void ViewUserWindow_Load(object sender, EventArgs e)
        {
            FrontDeskUserModel FDUM = new FrontDeskUserModel();
            list = FDUM.GetUserInfo("", true);

            for (int i = 0; i < list.Count(); i++)
            {
                frontDeskUserInfoBindingSource.Add(list[i]);
            }
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellMouseEventArgs e)
        {
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
    }
}
