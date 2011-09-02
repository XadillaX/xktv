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
using 前台系统.Properties;
using System.Threading;

namespace 前台系统
{
    public partial class MainWindow : Form
    {
        SqlConnection conn;
        ModelMachine MM;

        String Username;
        int UID;

        // 包厢按钮
        private Button[] MachineButton = new Button[256];
        private int BtnCount = 0;
        private const int BtnWidth = 128;
        private const int BtnHeight = 128;
        private const int BtnMinMargin = 15;

        public Object CriSection = new Object();

        // 线程数组(还不知道要用几个) 林莹莹 2011/9/2
        private Thread[] th = new Thread[16];

        public MainWindow(int _UID, String _Username, SqlConnection _conn)
        {
            InitializeComponent();

            Username = _Username;
            UID = _UID;

            conn = _conn;
            MM = new ModelMachine(conn);
        }

        private void MainWindow_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }

        // 线程函数 林莹莹 2011/9/2
        public void ThreadFunc()
        {
            while (true)
            {
                DateTime now = DateTime.Now;
                Monitor.Enter(CriSection);

                // 获取列表
                SqlDataReader dr = MM.GetMachineInfo_CloseByYourself("MachineNo, Status, ShutTime", "");
                String[] ToUpdate = new String[256];
                int ToUpdateCount = 0;

                // 一一对照时间
                while (dr.Read())
                {
                    if (dr["Status"].ToString() == "有客" && DateTime.Parse(dr["ShutTime"].ToString()).CompareTo(now) <= 0)
                    {
                        ToUpdate[ToUpdateCount++] = dr["MachineNo"].ToString();
                        for (int i = 0; i < BtnCount; i++)
                        {
                            if (dr["MachineNo"].ToString() == MachineButton[i].Text.ToString())
                            {
                                MachineButton[i].BackColor = Color.Red;
                                break;
                            }
                        }
                    }
                }
                dr.Close();
                MM.CloseConn();

                // 更新状态在数据库中
                MM.SetStatus("待清理", ToUpdate, ToUpdateCount);

                Monitor.Exit(CriSection);

                /** 半分钟更新一次机器状态 */
                Thread.Sleep(30000);
            }
        }

        private void MachineReposition()
        {
            int EachRowCount = (Panel.Width - BtnMinMargin) / (BtnWidth + BtnMinMargin);
            int RowCount = BtnCount / EachRowCount;
            if (BtnCount % EachRowCount != 0) RowCount++;
            int Margin = (Panel.Width - EachRowCount * BtnWidth) / (EachRowCount + 1);

            int StartX = Margin;
            int StartY = BtnMinMargin;

            int x = StartX;
            int y = StartY;

            Monitor.Enter(CriSection);
            for (int i = 0; i < RowCount; i++)
            {
                x = StartX;
                for (int j = 0; j < EachRowCount; j++)
                {
                    int idx = (i * EachRowCount) + j;
                    if (idx >= BtnCount) break;

                    MachineButton[idx].Top = y;
                    MachineButton[idx].Left = x;

                    x += (Margin + BtnWidth);
                }

                y += (BtnMinMargin + BtnHeight);
            }
            Monitor.Exit(CriSection);
        }

        private void Machine_Select(object sender, EventArgs e)
        {
            Button btn = (Button)sender;

            // 说明在待清理
            if (btn.BackColor == Color.Red)
            {
                if (MessageBox.Show("是否变为 \"清理中\" 状态？", "询问", MessageBoxButtons.YesNo) == DialogResult.Yes)
                {
                    if (MM.SetStatus("清理中", btn.Text.ToString()))
                    {
                        btn.BackColor = Color.Transparent;
                        btn.BackgroundImage = Resources.Recycle;
                    }
                    else
                    {
                        MessageBox.Show("系统错误，请稍后再试。");
                    }
                }
            }
        }

        private void MainWindow_Load(object sender, EventArgs e)
        {
            // 获取数据
            SqlDataReader dr = MM.GetMachineInfo_CloseByYourself("*", "");
            if (dr == null)
            {
                dr.Close();
                MM.CloseConn();
                return;
            }

            // 新建按钮
            Font BtnFont = new Font("微软雅黑", 20);
            int i = 0;
            while (dr.Read() != false)
            {
                MachineButton[i] = new Button();
                MachineButton[i].Width = BtnWidth;
                MachineButton[i].Height = BtnHeight;
                MachineButton[i].Font = BtnFont;
                MachineButton[i].FlatStyle = FlatStyle.Popup;
                MachineButton[i].BackgroundImageLayout = ImageLayout.Zoom;
                MachineButton[i].Click += Machine_Select;

                // 状态图片
                switch (dr["Status"].ToString())
                {
                case "空闲":
                    {
                        MachineButton[i].BackgroundImage = Resources.GOM;
                        break;
                    }

                case "待清理":
                    {
                        MachineButton[i].BackColor = Color.Red;
                        MachineButton[i].BackgroundImage = Resources.Media_Player;

                        break;
                    }

                case "有客":
                    {
                        MachineButton[i].BackgroundImage = Resources.Media_Player;
                        break;
                    }

                case "清理中":
                    {
                        MachineButton[i].BackgroundImage = Resources.Recycle;
                        break;
                    }

                default:
                    {
                        MachineButton[i].BackgroundImage = Resources.Headset;
                        break;
                    }
                }

                // 创建Tooltip
                ToolTip tt = new ToolTip();
                tt.AutoPopDelay = 5000;
                tt.InitialDelay = 500;
                tt.ReshowDelay = 500;
                tt.ShowAlways = true;
                tt.SetToolTip(MachineButton[i], dr["TypeName"].ToString());

                MachineButton[i].Text = dr["MachineNo"].ToString();
                MachineButton[i].Show();
                Panel.Controls.Add(MachineButton[i]);

                i++;
            }
            BtnCount = i;
            dr.Close();
            MM.CloseConn();

            // 重定位
            MachineReposition();

            // 监听线程1
            th[0] = new Thread(new ThreadStart(ThreadFunc));
            th[0].IsBackground = true;
            th[0].Start();
        }

        private void MainWindow_Resize(object sender, EventArgs e)
        {
            MachineReposition();
        }

        private void 退出QToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
