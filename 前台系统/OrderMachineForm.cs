using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Data.SqlClient;
using System.Text.RegularExpressions;

namespace 前台系统
{
    public partial class OrderMachineForm : Form
    {
        private String MachineNo;
        private String TypeNo;
        private String TypeName;
        private SqlConnection conn;
        private Model.ModelMachine MM;
        private Model.ModelConfig MC;
        private Double[] Prices = new Double[6];
        private int NightStart;
        private int NightEnd;
        private bool IsNight = false;

        public bool IsInt(String value)
        {
            return Regex.IsMatch(value, @"^[+-]?\d*$");
        }

        public bool IsNumeric(String value)
        {
            return Regex.IsMatch(value, @"^[+-]?\d*[.]?\d*$");
        }

        public bool IsUnsigned(String value)
        {
            return Regex.IsMatch(value, @"^\d*[.]?\d*$");
        }

        public OrderMachineForm(String _MachineNo, SqlConnection _conn)
        {
            InitializeComponent();

            MachineNo = _MachineNo;
            conn = _conn;

            MM = new Model.ModelMachine(conn);
            MC = new Model.ModelConfig(conn);
        }

        private void OrderMachineForm_Load(object sender, EventArgs e)
        {
            Text = "下单 :: " + MachineNo;
            MachineNameLabel.Text = MachineNo;
            Update();

            // 配置
            NightStart = Convert.ToInt32(MC.GetValue("NightStart"));
            NightEnd = Convert.ToInt32(MC.GetValue("NightEnd"));

            // 查找数据
            SqlDataReader dr = MM.GetMachineInfo_CloseByYourself("Machine.TypeNo", "MachineNo = '" + MachineNo + "'");
            if (null == dr)
            {
                MM.CloseConn();
                MessageBox.Show("包厢数据访问出错！");
                Close();
                return;
            }
            if (!dr.Read())
            {
                dr.Close();
                MM.CloseConn();
                MessageBox.Show("包厢数据访问出错！");
                Close();
                return;
            }
            TypeNo = dr["TypeNo"].ToString();
            dr.Close();
            MM.CloseConn();

            // 价格
            Dictionary<String, String>[] List = MM.GetMachineType("TypeNo = '" + TypeNo + "'");
            if (List.Count() == 0)
            {
                MessageBox.Show("包厢类型数据访问出错！");
                Close();
                return;
            }
            TypeName = List[0]["TypeName"];
            TypeNameLabel.Text = "[" + TypeName + "]";
            for (int i = 0; i < 6; i++)
            {
                Prices[i] = Convert.ToDouble(List[0]["Price" + i.ToString()]);
            }

            // 时间
            DateTime Now = DateTime.Now;
            ChooseDate.Value = Now;
            HourBox.Value = Now.Hour;
            MinuteBox.Value = Now.Minute;
        }

        private void SetWholeNight(bool bNight)
        {
            if (bNight)
            {
                LastLong.Enabled = false;
                LabelHour.Text = "包夜";
                IsNight = true;
            }
            else
            {
                LastLong.Enabled = true;
                LabelHour.Text = "小时";
                IsNight = false;
            }
        }

        private void HourBox_ValueChanged(object sender, EventArgs e)
        {
            // 包夜时间段跨天
            if (NightStart >= NightEnd)
            {
                if (HourBox.Value >= NightStart || HourBox.Value <= NightEnd)
                {
                    SetWholeNight(true);
                }
                else SetWholeNight(false);
            }
            else
            {
                if (HourBox.Value >= NightStart && HourBox.Value <= NightEnd)
                {
                    SetWholeNight(true);
                }
                else SetWholeNight(false);
            }
        }

        private void EditVIP_Click(object sender, EventArgs e)
        {

        }
    }
}
