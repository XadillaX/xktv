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
    public partial class SearchFreeMachineForm : Form
    {
        SqlConnection conn;
        ModelMachine MM;
        Dictionary<string, string>[] TypeList;
        MainWindow MW;
        String Username;

        public SearchFreeMachineForm(SqlConnection _conn, MainWindow _MW, String _Username)
        {
            InitializeComponent();
            MW = _MW;
            Username = _Username;

            conn = _conn;
            MM = new ModelMachine(conn);
        }

        private void SearchFreeMachineForm_Load(object sender, EventArgs e)
        {
            // 获取中...
            TypeSelect.SelectedIndex = 0;
            TypeSelect.Update();

            // 类型
            TypeList = MM.GetMachineType("");
            TypeSelect.Items.Clear();
            for (int i = 0; i < TypeList.Count(); i++)
            {
                TypeSelect.Items.Add(TypeList[i]["TypeName"].ToString());
            }

            // 默认选中第0个
            TypeSelect.SelectedIndex = 0;
        }

        private void TypeSelect_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (TypeSelect.Items[TypeSelect.SelectedIndex].ToString() == "获取中...")
            {
                //MessageBox.Show("获取中...");
                return;
            }

            // 获取下标
            int Idx = TypeSelect.SelectedIndex;
            String p = "";
            p += ("星期中间白天: " + TypeList[Idx]["Price0"] + "元\n\n");
            p += ("星期中间黄金: " + TypeList[Idx]["Price1"] + "元\n\n");
            p += ("星期中间包夜: " + TypeList[Idx]["Price2"] + "元\n\n");
            p += ("周末白天: " + TypeList[Idx]["Price3"] + "元\n\n");
            p += ("周末黄金: " + TypeList[Idx]["Price4"] + "元\n\n");
            p += ("周末包夜: " + TypeList[Idx]["Price5"] + "元\n\n");

            Prices.Text = p;
        }

        private void Search_Click(object sender, EventArgs e)
        {
            if (TypeSelect.Items[TypeSelect.SelectedIndex].ToString() == "获取中...")
            {
                return;
            }

            DateTime StartTime = DateTime.Now;

            // 获取下标
            int Idx = TypeSelect.SelectedIndex;
            String TypeName = TypeSelect.Items[Idx].ToString();

            // 清理ListBox
            Results.ClearSelected();
            Results.Items.Clear();

            int RstCnt = 0;
            int MachineCount = MW.GetMachineCount();
            for (int i = 0; i < MachineCount; i++)
            {
                // 符合条件
                if (MW.GetMachineInfo(i, "Status") == "空闲" && MW.GetMachineInfo(i, "TypeName") == TypeName)
                {
                    Results.Items.Add(MW.GetMachineInfo(i, "MachineNo"));
                    RstCnt++;
                }
            }

            DateTime EndTime = DateTime.Now;
            TimeSpan TS = EndTime - StartTime;

            ResultCount.Text = "共查询到 " + RstCnt.ToString() + " 个空闲包厢\n";
            ResultCount.Text += "耗时 " + ((float)(TS.Milliseconds) / 1000.0f).ToString() + " 秒。";
        }

        private void Record_Click(object sender, EventArgs e)
        {
            // 获取下标
            int Idx = Results.SelectedIndex;
            if (Idx == -1)
            {
                MessageBox.Show("未选中任何包厢！", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            OrderMachineForm OMF = new OrderMachineForm(Results.Items[Idx].ToString(), conn, Username);
            OMF.ShowDialog();
        }
    }
}
