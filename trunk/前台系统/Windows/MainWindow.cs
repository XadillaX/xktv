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
        private String[] TypeNames = new String[256];
        private String[] Status = new String[256];
        
        private int BtnCount = 0;
        private const int BtnWidth = 128;
        private const int BtnHeight = 128;
        private const int BtnMinMargin = 15;
        public Object CriSection = new Object();

        private ContextMenuStrip[] Menus = new ContextMenuStrip[256];

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
            ModelMachine mm = new ModelMachine(new SqlConnection("Server=localhost;DataBase=ktv;Uid=sa;pwd=;"));

            while (true)
            {
                DateTime now = DateTime.Now;
                Monitor.Enter(CriSection);

                // 获取列表
                SqlDataReader dr = mm.GetMachineInfo_CloseByYourself("MachineNo, Status, ShutTime", "");
                String[] ToUpdate = new String[256];
                int ToUpdateCount = 0;

                // 一一对照时间
                while (dr.Read())
                {
                    // 同步状态
                    for (int i = 0; i < BtnCount; i++)
                    {
                        if (dr["MachineNo"].ToString() == MachineButton[i].Text.ToString())
                        {
                            SetState(i, dr["Status"].ToString());
                            break;
                        }
                    }

                    // 设置 待清理 状态
                    if (dr["Status"].ToString() == "有客" && DateTime.Parse(dr["ShutTime"].ToString()).CompareTo(now) <= 0)
                    {
                        ToUpdate[ToUpdateCount++] = dr["MachineNo"].ToString();
                        for (int i = 0; i < BtnCount; i++)
                        {
                            if (dr["MachineNo"].ToString() == MachineButton[i].Text.ToString())
                            {
                                SetState(i, "待清理");
                                break;
                            }
                        }
                    }
                }
                dr.Close();
                mm.CloseConn();

                // 更新状态在数据库中
                mm.SetStatus("待清理", ToUpdate, ToUpdateCount);

                Monitor.Exit(CriSection);

                /** 一秒钟更新一次机器状态 */
                Thread.Sleep(1000);
            }
        }

        public String GetMachineInfo(int Idx, String Key)
        {
            if (Idx >= BtnCount) return "";

            Monitor.Enter(CriSection);
            switch (Key)
            {
            case "TypeName":
                {
                    Monitor.Exit(CriSection);
                    return TypeNames[Idx];
                    break;
                }

            case "Status":
                {
                    Monitor.Exit(CriSection);
                    return Status[Idx];
                    break;
                }

            case "MachineNo":
                {
                    Monitor.Exit(CriSection);
                    return MachineButton[Idx].Text;
                    break;
                }

            default:
                {
                    Monitor.Exit(CriSection);
                    return "";
                    break;
                }
            }
        }

        public int GetMachineCount() { return BtnCount; }

        //
        // 摘要：
        //     为下标为Idx的包厢按钮设置相应的状态显示效果
        //
        public void SetState(int Idx, String _Status)
        {
            // 状态枚举
            Button Btn;
            try
            {
                Btn = MachineButton[Idx];
            }
            catch (Exception e)
            {
                // 可能下标越界
                return;
            }

            // 图片及背景色
            Monitor.Enter(CriSection);
            switch (_Status)
            {
            case "空闲":
                {
                    Btn.BackgroundImage = Resources.GOM;
                    Btn.BackColor = Color.White;

                    Menus[Idx].Items.Clear();
                    ToolStripMenuItem Item = new ToolStripMenuItem("设置为故障机(&B)");
                    Item.Name = "BugMenu" + Idx.ToString();
                    Item.Click += ToBug;
                    Menus[Idx].Items.Add(Item);

                    break;
                }

            case "待清理":
                {
                    Btn.BackgroundImage = Resources.Media_Player;
                    Btn.BackColor = Color.Red;

                    Menus[Idx].Items.Clear();
                    ToolStripMenuItem Item = new ToolStripMenuItem("设置为故障机(&B)");
                    Item.Name = "BugMenu" + Idx.ToString();
                    Item.Click += ToBug;
                    Menus[Idx].Items.Add(Item);

                    break;
                }

            case "有客":
                {
                    Btn.BackgroundImage = Resources.Media_Player;
                    Btn.BackColor = Color.Yellow;

                    Menus[Idx].Items.Clear();
                    ToolStripMenuItem Item = new ToolStripMenuItem("设置为故障机(&B)");
                    Item.Name = "BugMenu" + Idx.ToString();
                    Item.Click += ToBug;
                    Menus[Idx].Items.Add(Item);

                    break;
                }

            case "清理中":
                {
                    Btn.BackgroundImage = Resources.Recycle;
                    Btn.BackColor = Color.Green;

                    Menus[Idx].Items.Clear();
                    ToolStripMenuItem Item = new ToolStripMenuItem("设置为故障机(&B)");
                    Item.Name = "BugMenu" + Idx.ToString();
                    Item.Click += ToBug;
                    Menus[Idx].Items.Add(Item);

                    break;
                }

            case "故障":
                {
                    Btn.BackgroundImage = Resources.Wrench;
                    Btn.BackColor = Color.Gray;

                    Menus[Idx].Items.Clear();
                    ToolStripMenuItem Item = new ToolStripMenuItem("故障已修复(&B)");
                    Item.Name = "CancelBugMenu" + Idx.ToString();
                    Item.Click += CancelBug;
                    Menus[Idx].Items.Add(Item);

                    break;
                }

            default:
                {
                    Btn.BackgroundImage = Resources.Headset;
                    Btn.BackColor = Color.Transparent;
                    break;
                }
            }

            Status[Idx] = _Status;
            Monitor.Exit(CriSection);
        }

        private void MachineReposition()
        {
            int EachRowCount = (Panel.Width - BtnMinMargin) / (BtnWidth + BtnMinMargin);
            
            // 修复BUG: 不然下面会除0
            if (EachRowCount == 0) EachRowCount = 1;
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
            int Idx = Convert.ToInt32(btn.Name.Substring(10));

            // 说明在待清理
            if (Status[Idx] == "待清理")
            {
                if (MessageBox.Show("是否变为 \"清理中\" 状态？", "询问", MessageBoxButtons.YesNo) == DialogResult.Yes)
                {
                    if (MM.SetStatus("清理中", btn.Text.ToString()))
                    {
                        SetState(Idx, "清理中");
                    }
                    else
                    {
                        MessageBox.Show("系统错误，请稍后再试。");
                    }
                }
            }
            else
            // 清理中
            if (Status[Idx] == "清理中")
            {
                if (MessageBox.Show("是否变为 \"空闲\" 状态？", "询问", MessageBoxButtons.YesNo) == DialogResult.Yes)
                {
                    if (MM.SetStatus("空闲", btn.Text.ToString()))
                    {
                        SetState(Idx, "空闲");
                    }
                    else
                    {
                        MessageBox.Show("系统错误，请稍后再试。");
                    }
                }
            }
            else
            // 空闲
            if (Status[Idx] == "空闲")
            {
                OrderMachineForm OMF = new OrderMachineForm(MachineButton[Idx].Text, conn, Username);
                OMF.ShowDialog();
            }
            else
            // 有客
            if (Status[Idx] == "有客")
            {
                ContinueMachineForm CMF = new ContinueMachineForm(conn, btn.Text.ToString());
                CMF.ShowDialog();
            }
        }

        private void MainWindow_Load(object sender, EventArgs e)
        {
            // 用户名
            ShowUsername.Text = "操作员: " + Username;

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
                Menus[i] = new ContextMenuStrip();
                Menus[i].Name = "MenuName" + i.ToString();
                MachineButton[i].ContextMenuStrip = Menus[i];

                // 状态图片
                SetState(i, dr["Status"].ToString());

                // 创建Tooltip
                ToolTip tt = new ToolTip();
                tt.AutoPopDelay = 5000;
                tt.InitialDelay = 500;
                tt.ReshowDelay = 500;
                tt.ShowAlways = true;
                tt.SetToolTip(MachineButton[i], dr["TypeName"].ToString());
                TypeNames[i] = dr["TypeName"].ToString();

                MachineButton[i].Name = "MachineIdx" + i.ToString();
                MachineButton[i].Text = dr["MachineNo"].ToString();
                MachineButton[i].Show();
                Panel.Controls.Add(MachineButton[i]);

                i++;
            }
            BtnCount = i;
            dr.Close();
            MM.CloseConn();
            MachineCount.Text = "包厢数量: " + BtnCount.ToString();

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

        private void 空闲包厢FToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SearchFreeMachineForm SFMF = new SearchFreeMachineForm(conn, this, Username);
            SFMF.ShowDialog();
        }

        private void 包厢一览VToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MachineStateView MSV = new MachineStateView(conn, Username);
            MSV.ShowDialog();
        }

        private void ToBug(object sender, EventArgs e)
        {
            // BugMenu
            // MessageBox.Show(((ToolStripMenuItem)sender).GetCurrentParent().ToString());
            int Idx = Convert.ToInt32(((ToolStripItem)sender).Name.Substring(7));

            if (MessageBox.Show("是否变为 \"故障\" 状态？", "询问", MessageBoxButtons.YesNo) == DialogResult.Yes)
            {
                if (MM.SetStatus("故障", MachineButton[Idx].Text.ToString()))
                {
                    SetState(Idx, "故障");
                }
                else
                {
                    MessageBox.Show("系统错误，请稍后再试。");
                }
            }
        }

        private void CancelBug(object sender, EventArgs e)
        {
            // CancelBugMenu
            // MessageBox.Show(((ToolStripMenuItem)sender).GetCurrentParent().ToString());
            int Idx = Convert.ToInt32(((ToolStripItem)sender).Name.Substring(13));

            if (MessageBox.Show("是否变为 \"空闲\" 状态？", "询问", MessageBoxButtons.YesNo) == DialogResult.Yes)
            {
                if (MM.SetStatus("空闲", MachineButton[Idx].Text.ToString()))
                {
                    SetState(Idx, "空闲");
                }
                else
                {
                    MessageBox.Show("系统错误，请稍后再试。");
                }
            }
        }

        private void vIP用户充值充值ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ChargeForm CF = new ChargeForm(conn);
            CF.ShowDialog();
        }

        private void 新VIP用户NToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Windows.RegForm RF = new 前台系统.Windows.RegForm(conn);
            RF.ShowDialog();
        }
    }
}
