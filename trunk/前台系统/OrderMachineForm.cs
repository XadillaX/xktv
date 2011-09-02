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
        private String VIPNo;
        private SqlConnection conn;
        private Model.ModelMachine MM;
        private Model.ModelConfig MC;
        private Model.ModelVIP MV;
        private Double[] Prices = new Double[6];
        private int NightStart;
        private int NightEnd;
        private bool IsNight = false;
        private const int GoldTime = 18;                        // 六点黄金时段，新闻三十分;-)
        private Dictionary<String, String> VIPInfo;
        private int CreditRate;
        private int CreditExchange;
        private Double Rebate;
        private Double RstPrice;
        private Double RstPriceFact;

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

        public String Username;
        public OrderMachineForm(String _MachineNo, SqlConnection _conn, String _Username)
        {
            InitializeComponent();

            MachineNo = _MachineNo;
            conn = _conn;
            Username = _Username;

            MM = new Model.ModelMachine(conn);
            MC = new Model.ModelConfig(conn);
            MV = new Model.ModelVIP(conn);
        }

        private void GetVIPInfoFromDatabase(String VIPNo)
        {
            // VIP信息
            Dictionary<String, String> info = MV.GetVIPInfo(VIPNo);
            if (info == null)
            {
                MessageBox.Show("不存在的VIP会员！");
                return;
            }

            // 显示
            VIPInfo = info;
            VIPNo = VIPInfo["VIPNo"];
            LVIPName.Text = "会员姓名: " + VIPInfo["VIPName"];
            LVIPID.Text = "身份证号码: " + VIPInfo["VIPID"];
            LBalance.Text = "余额: " + VIPInfo["Balance"];
            LCurExp.Text = "剩余积分: " + VIPInfo["CurExp"];
            LTotExp.Text = "已用积分: " + VIPInfo["TotExp"];

            CalcPrice();
        }

        private void OrderMachineForm_Load(object sender, EventArgs e)
        {
            Text = "下单 :: " + MachineNo;
            MachineNameLabel.Text = MachineNo;
            Update();

            // 配置
            NightStart = Convert.ToInt32(MC.GetValue("NightStart"));
            NightEnd = Convert.ToInt32(MC.GetValue("NightEnd"));
            CreditRate = Convert.ToInt32(MC.GetValue("CreditRate"));
            CreditExchange = Convert.ToInt32(MC.GetValue("CreditExchange"));
            Rebate = Convert.ToDouble(MC.GetValue("Rebate"));

            GetVIPInfoFromDatabase("0000000000");

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

            UseExp.Maximum = 0;
            UseBalance.Maximum = 0;

            CalcPrice();
        }

        private void SetWholeNight(bool bNight)
        {
            if (bNight)
            {
                LastLong.Enabled = false;
                LabelHour.Text = "包夜";
                IsNight = true;
                UseExp.Enabled = false;
            }
            else
            {
                LastLong.Enabled = true;
                LabelHour.Text = "小时";
                IsNight = false;
                UseExp.Enabled = true;
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

            // 时长
            if (NightStart < HourBox.Value && HourBox.Value + LastLong.Value >= 24 && (HourBox.Value + LastLong.Value) % 24 > NightStart)
            {
                LastLong.Value -= (((HourBox.Value + LastLong.Value) % 24) - NightStart);
            }
            else
            if (NightStart > HourBox.Value && HourBox.Value + LastLong.Value > NightStart)
            {
                LastLong.Value = NightStart - HourBox.Value;
            }

            // 积分换时
            if (VIPInfo != null && VIPInfo["VIPNo"] != "0000000000")
            {
                UseExp.Maximum = Convert.ToInt32(VIPInfo["CurExp"]) / CreditExchange;
                if (UseExp.Maximum > LastLong.Value) UseExp.Maximum = LastLong.Value;
            }
            CalcPrice();

            // 使用余额
            if (VIPInfo != null && VIPInfo["VIPNo"] != "0000000000")
            {
                UseBalance.Maximum = Convert.ToDecimal(VIPInfo["Balance"]);
                if ((Double)UseBalance.Maximum > RstPrice) UseBalance.Maximum = (Decimal)RstPrice;
            }

            // 算钱
            CalcPrice();
        }

        private void CalcPrice()
        {
            // 日期
            DateTime dt = ChooseDate.Value;
            int IdxStart = (dt.DayOfWeek == DayOfWeek.Saturday || dt.DayOfWeek == DayOfWeek.Sunday) ? 2 : 0;

            if (IsNight)
            {
                // 如果包夜
                RstPrice = Prices[IdxStart + 2];

                // 如果是会员
                if (null != VIPInfo && VIPInfo["VIPNo"] != "0000000000")
                {
                    RstPrice *= Rebate;
                }
            }
            else
            {
                // 除去积分(把积分放到前面的小时用，因为黄金时段在非黄金时段的后面)
                int PayedLastLong = (int)LastLong.Value - (int)UseExp.Value;

                int StartH = ((int)HourBox.Value + (int)UseExp.Value) % 24;

                // 算各小时的钱
                RstPrice = 0.0f;
                for (int i = StartH; i < StartH + PayedLastLong; i++)
                {
                    if (i < GoldTime) RstPrice += Prices[IdxStart];
                    else RstPrice += Prices[IdxStart + 1];
                }

                // 如果是会员
                if (null != VIPInfo && VIPInfo["VIPNo"] != "0000000000")
                {
                    RstPrice *= Rebate;
                }
            }

            // 保留两位
            RstPrice = ((Double)((int)(RstPrice * 100))) / 100.0f;

            // 实际
            RstPriceFact = RstPrice - (Double)UseBalance.Value;

            LBudget.Text = "预算: " + RstPriceFact.ToString("0.00");
        }

        private void EditVIP_Click(object sender, EventArgs e)
        {
            GetVIPInfoFromDatabase(EVIPNo.Text);

            // 积分换时
            if (VIPInfo != null && VIPInfo["VIPNo"] != "0000000000")
            {
                UseExp.Maximum = Convert.ToInt32(VIPInfo["CurExp"]) / CreditExchange;
                if (UseExp.Maximum > LastLong.Value) UseExp.Maximum = LastLong.Value;
            }
            CalcPrice();

            // 使用余额
            if (VIPInfo != null && VIPInfo["VIPNo"] != "0000000000")
            {
                UseBalance.Maximum = Convert.ToDecimal(VIPInfo["Balance"]);
                if ((Double)UseBalance.Maximum > RstPrice) UseBalance.Maximum = (Decimal)RstPrice;
            }
            CalcPrice();
        }

        private void LastLong_ValueChanged(object sender, EventArgs e)
        {
            // 时长
            if (NightStart < HourBox.Value && HourBox.Value + LastLong.Value >= 24 && (HourBox.Value + LastLong.Value) % 24 > NightStart)
            {
                LastLong.Value -= (((HourBox.Value + LastLong.Value) % 24) - NightStart);
            }
            else
            if (NightStart > HourBox.Value && HourBox.Value + LastLong.Value > NightStart)
            {
                LastLong.Value = NightStart - HourBox.Value;
            }

            // 积分换时
            if (VIPInfo != null && VIPInfo["VIPNo"] != "0000000000")
            {
                UseExp.Maximum = Convert.ToInt32(VIPInfo["CurExp"]) / CreditExchange;
                if (UseExp.Maximum > LastLong.Value) UseExp.Maximum = LastLong.Value;
            }
            CalcPrice();

            // 使用余额
            if (VIPInfo != null && VIPInfo["VIPNo"] != "0000000000")
            {
                UseBalance.Maximum = Convert.ToDecimal(VIPInfo["Balance"]);
                if ((Double)UseBalance.Maximum > RstPrice) UseBalance.Maximum = (Decimal)RstPrice;
            }

            CalcPrice();
        }

        private void EVIPNo_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyValue == 13)
            {
                GetVIPInfoFromDatabase(EVIPNo.Text);

                // 积分换时
                if (VIPInfo != null && VIPInfo["VIPNo"] != "0000000000")
                {
                    UseExp.Maximum = Convert.ToInt32(VIPInfo["CurExp"]) / CreditExchange;
                    if (UseExp.Maximum > LastLong.Value) UseExp.Maximum = LastLong.Value;
                }
                CalcPrice();

                // 使用余额
                if (VIPInfo != null && VIPInfo["VIPNo"] != "0000000000")
                {
                    UseBalance.Maximum = Convert.ToDecimal(VIPInfo["Balance"]);
                    if ((Double)UseBalance.Maximum > RstPrice) UseBalance.Maximum = (Decimal)RstPrice;
                }

                CalcPrice();
            }
        }

        private void UseExp_ValueChanged(object sender, EventArgs e)
        {
            // 使用余额
            if (VIPInfo != null && VIPInfo["VIPNo"] != "0000000000")
            {
                UseBalance.Maximum = Convert.ToDecimal(VIPInfo["Balance"]);
                if ((Double)UseBalance.Maximum > RstPrice) UseBalance.Maximum = (Decimal)RstPrice;
            }

            CalcPrice();
        }

        private void UseBalance_ValueChanged(object sender, EventArgs e)
        {
            CalcPrice();
        }

        private void Cancel_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void OK_Click(object sender, EventArgs e)
        {
            OrderData od = new OrderData();
            od.MachineNo = MachineNo;
            od.Money = RstPriceFact;
            od.MoneyFact = (Double)Income.Value;
            od.MoneyGiveBack = od.MoneyFact - od.Money;
            if (od.MoneyGiveBack < 0)
            {
                MessageBox.Show("金额不足！");
                return;
            }
            DateTime tmp = ChooseDate.Value;
            od.StartTime = new DateTime(tmp.Year, tmp.Month, tmp.Day, (int)HourBox.Value, (int)MinuteBox.Value, 0);
            od.ShutTime = od.StartTime.AddHours((Double)LastLong.Value);
            od.IsNight = IsNight;
            if (IsNight)
            {
                // 包夜
                od.ShutTime = new DateTime(tmp.Year, tmp.Month, tmp.Day, NightEnd, 0, 0);
                od.UseExp = 0;

                if (NightStart > NightEnd) od.ShutTime.AddDays(1);
            }

            od.Time = DateTime.Now;
            od.TypeName = TypeName;
            od.UseBalance = (Double)UseBalance.Value;
            od.UseExp = (int)UseExp.Value;
            od.Username = Username;
            od.VIPNo = (VIPInfo == null) ? "0000000000" : VIPInfo["VIPNo"];

            ChkOrderMachineForm COMF = new ChkOrderMachineForm(conn, od, this);
            COMF.ShowDialog();
        }
    }
}
