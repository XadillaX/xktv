using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Data.SqlClient;
using System.Windows.Forms;

namespace 前台系统
{
    public partial class MachineStateView : Form
    {
        private SqlConnection conn;
        private Model.ModelMachine MM;
        private Dictionary<String, String>[] TypeInfo;
        private String Username;

        public MachineStateView(SqlConnection _conn, String _Username)
        {
            InitializeComponent();

            conn = _conn;

            MM = new Model.ModelMachine(conn);
        }

        private void RefreshData()
        {
            DataGrid.Rows.Clear();
            SqlDataReader dr = MM.GetMachineInfo_CloseByYourself("*", "");

            while (dr.Read())
            {
                DataGridViewRow dgvr = new DataGridViewRow();
                String[] Obj = new String[5];
                dgvr.SetValues((Object[])Obj);

                Obj[0] = dr["MachineNo"].ToString();
                for (int i = 0; i < TypeInfo.Count(); i++)
                {
                    if (dr["TypeNo"].ToString() == TypeInfo[i]["TypeNo"])
                    {
                        Obj[1] = TypeInfo[i]["TypeName"];
                        break;
                    }
                }
                Obj[2] = dr["Status"].ToString();
                Obj[3] = dr["ShutTime"].ToString();

                if (Obj[2] != "有客")
                {
                    Obj[3] = "-";
                    Obj[4] = "-";
                }
                else
                {
                    DateTime Now = DateTime.Now;
                    DateTime ShutTime = Convert.ToDateTime(Obj[3]);

                    TimeSpan ts = ShutTime - Now;
                    Obj[4] = (ts.TotalMinutes).ToString("0") + " 分钟";
                }

                for (int i = 0; i < 5; i++)
                {
                    DataGridViewCell dgvc = new DataGridViewTextBoxCell();

                    dgvc.Value = Obj[i];
                    dgvr.Cells.Add(dgvc);
                }
                DataGrid.Rows.Add(dgvr);
            }

            dr.Close();
            MM.CloseConn();

            DataGrid.Sort(new RowComparer(System.Data.SqlClient.SortOrder.Ascending));
        }

        private void MachineStateView_Load(object sender, EventArgs e)
        {
            TypeInfo = MM.GetMachineType("");
            if (null == TypeInfo)
            {
                MessageBox.Show("包厢类型获取错误！");
                Close();
                return;
            }

            RefreshData();
        }

        private void Refresh_Click(object sender, EventArgs e)
        {
            RefreshData();
        }

        private class RowComparer : System.Collections.IComparer
        {
            private static int sortOrderModifier = 1;
            Dictionary<String, int> StatusOrder;

            public RowComparer(System.Data.SqlClient.SortOrder sortOrder)
            {
                if (sortOrder == System.Data.SqlClient.SortOrder.Descending)
                {
                    sortOrderModifier = -1;
                }
                else
                    if (sortOrder == System.Data.SqlClient.SortOrder.Ascending)
                {
                    sortOrderModifier = 1;
                }

                StatusOrder = new Dictionary<string, int>();
                StatusOrder["空闲"] = 0;
                StatusOrder["清理中"] = 1;
                StatusOrder["待清理"] = 2;
                StatusOrder["有客"] = 3;
                StatusOrder["故障"] = 4;
            }

            public int Compare(object x, object y)
            {
                DataGridViewRow a = (DataGridViewRow)x;
                DataGridViewRow b = (DataGridViewRow)y;

                int rst;
                if (StatusOrder[a.Cells[2].Value.ToString()] < StatusOrder[b.Cells[2].Value.ToString()])
                {
                    rst = -1;
                }
                else
                if (StatusOrder[a.Cells[2].Value.ToString()] > StatusOrder[b.Cells[2].Value.ToString()])
                {
                    rst = 1;
                }
                else
                {
                    if (a.Cells[2].Value.ToString() != "有客")
                    {
                        rst = String.Compare(a.Cells[0].Value.ToString(), b.Cells[0].Value.ToString());
                    }
                    else
                    {
                        String timea = a.Cells[4].Value.ToString().Substring(0, a.Cells[4].Value.ToString().Length - 3);
                        String timeb = b.Cells[4].Value.ToString().Substring(0, b.Cells[4].Value.ToString().Length - 3);

                        if (Convert.ToInt32(timea) < Convert.ToInt32(timeb))
                        {
                            rst = -1;
                        }
                        else rst = 1;
                    }
                }

                return rst * sortOrderModifier;
            }
        }

        private void DataGrid_CellMouseDoubleClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            if (e.RowIndex < 0) return;
            DataGridViewRow dgvr = DataGrid.Rows[e.RowIndex];

            RefreshData();

            String Status = dgvr.Cells[2].Value.ToString();
            String MachineNo = dgvr.Cells[0].Value.ToString();
            String TypeName = dgvr.Cells[1].Value.ToString();

            // 说明在待清理
            if (Status == "待清理")
            {
                if (MessageBox.Show(MachineNo + "[" + TypeName + "]" + " 是否变为 \"清理中\" 状态？", "询问", MessageBoxButtons.YesNo) == DialogResult.Yes)
                {
                    if (MM.SetStatus("清理中", MachineNo))
                    {
                        RefreshData();
                    }
                    else
                    {
                        MessageBox.Show("系统错误，请稍后再试。");
                    }
                }
            }
            else
            // 清理中
            if (Status == "清理中")
            {
                if (MessageBox.Show(MachineNo + "[" + TypeName + "]" + " 是否变为 \"空闲\" 状态？", "询问", MessageBoxButtons.YesNo) == DialogResult.Yes)
                {
                    if (MM.SetStatus("空闲", MachineNo))
                    {
                        RefreshData();
                    }
                    else
                    {
                        MessageBox.Show("系统错误，请稍后再试。");
                    }
                }
            }
            else
            // 空闲
            if (Status == "空闲")
            {
                OrderMachineForm OMF = new OrderMachineForm(MachineNo, conn, Username);
                OMF.ShowDialog();
                RefreshData();
            }
            else
            // 有客
            if (Status == "有客")
            {
                ContinueMachineForm CMF = new ContinueMachineForm(conn, MachineNo);
                CMF.ShowDialog();
                RefreshData();
            }
        }

        private void Cancel_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
