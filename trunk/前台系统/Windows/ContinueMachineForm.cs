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
using 前台系统.Class;

namespace 前台系统
{
    public partial class ContinueMachineForm : Form
    {
        private String MachineNo;
        private String TypeNo;
        private Dictionary<String, String> TypeInfo;

        private SqlConnection conn;

        private ModelMachine MM;
        private ModelVIP MV;
        private ModelExpRecord MER;
        private ModelConfig MC;

        // 订单信息
        private int ExpNo;
        private RecordInfo RI;
        private DateTime StartTime;
        private DateTime ShutTime;

        // 会员信息
        private String VIPNo;
        private Dictionary<String, String> VIPInfo;
        private Double[] Prices = new Double[6];

        // 配置信息
        private int NightStart;
        private int NightEnd;
        private int CreditRate;
        private int CreditExchange;
        private Double Rebate;

        private const int GoldTime = 18;

        private Double Price;
        private Double PriceWithBalance;

        private int LastLong;
        private int NightLong;

        public ContinueMachineForm(SqlConnection _conn, String _MachineNo)
        {
            InitializeComponent();

            conn = _conn;
            MachineNo = _MachineNo;

            MM = new ModelMachine(conn);
            MV = new ModelVIP(conn);
            MER = new ModelExpRecord(conn);
            MC = new ModelConfig(conn);
        }

        private void CalcPrice()
        {
            Double result = 0.0f;
            DateTime dt = ShutTime;
            int IdxStart = (dt.DayOfWeek == DayOfWeek.Saturday || dt.DayOfWeek == DayOfWeek.Sunday) ? 2 : 0;

            int H = ShutTime.Hour;
            int EndTime = Convert.ToInt32(BoxLastLong.Value);
            if(IsNight.Checked)
            {
                EndTime = Convert.ToInt32(BoxLastLong.Maximum);
            }

            for (int i = 0; i < EndTime; i++)
            {
                if (H < GoldTime)
                {
                    result += Prices[IdxStart + 0];
                }
                else result += Prices[IdxStart + 1];

                H = (H + 1) % 24;
            }

            // 如果有包夜
            if (IsNight.Checked)
            {
                dt = dt.AddHours(EndTime);
                IdxStart = (dt.DayOfWeek == DayOfWeek.Saturday || dt.DayOfWeek == DayOfWeek.Sunday) ? 2 : 0;

                result += Prices[IdxStart + 2];
            }

            LastLong = EndTime;

            // 如果是会员
            if (null != VIPInfo && VIPInfo["VIPNo"] != "0000000000")
            {
                result *= Rebate;
            }

            Price = result;

            PriceWithBalance = result - Convert.ToInt32(BoxUseBalance.Value);
            if (PriceWithBalance < 0)
            {
                PriceWithBalance = 0;
                BoxUseBalance.Value = Convert.ToDecimal(Price);
            }

            LMoney.Text = "预计付款: " + PriceWithBalance.ToString("0.00") + " 元 | 找零: ";
            LMoney.Text += ((Convert.ToDouble(BoxMoney.Value) - PriceWithBalance).ToString("0.00") + " 元");

            // 使用余额最大值
            BoxUseBalance.Maximum = Math.Min(Convert.ToDecimal(Price), Convert.ToDecimal(VIPInfo["Balance"]));
        }

        private void ContinueMachineForm_Load(object sender, EventArgs e)
        {
            MachineNameLabel.Text = MachineNo;

            // 获取信息
            SqlDataReader dr = MM.GetMachineInfo_CloseByYourself("ShutTime, StartTime, ExpNo, Machine.TypeNo", "Machine.MachineNo = '" + MachineNo + "'");
            if (dr.Read())
            {
                ExpNo = Convert.ToInt32(dr["ExpNo"].ToString());
                TypeNo = dr["TypeNo"].ToString();
                StartTime = Convert.ToDateTime(dr["StartTime"].ToString());
                ShutTime = Convert.ToDateTime(dr["ShutTime"].ToString());

                dr.Close();
                MM.CloseConn();
            }
            else
            {
                dr.Close();
                MM.CloseConn();
                MessageBox.Show("包厢信息获取错误！");

                Close();
                return;
            }

            // 获取包厢类型信息
            Dictionary<string, string>[] infolist = MM.GetMachineType("TypeNo = '" + TypeNo + "'");
            if (null == infolist)
            {
                MessageBox.Show("包厢类型信息获取错误！");

                Close();
                return;
            }
            TypeInfo = infolist[0];
            for (int i = 0; i < 6; i++)
            {
                Prices[i] = Convert.ToDouble(TypeInfo["Price" + i.ToString()]);
            }

            // 消费信息
            RI = MER.GetRecordInfo(ExpNo);
            if (null == RI)
            {
                MessageBox.Show("消费记录信息获取错误！");

                Close();
                return;
            }

            // 会员信息
            VIPNo = RI.VIPNo;
            VIPInfo = MV.GetVIPInfo(VIPNo);
            if (null == VIPInfo)
            {
                MessageBox.Show("VIP会员信息获取错误！");

                Close();
                return;
            }

            // 配置信息
            NightStart = MC.GetValueInt("NightStart");
            NightEnd = MC.GetValueInt("NightEnd");
            CreditRate = MC.GetValueInt("CreditRate");
            CreditExchange = MC.GetValueInt("CreditExchange");
            Rebate = MC.GetValueDouble("Rebate");

            // 原先是否包夜
            DateTime tns = new DateTime(StartTime.Year, StartTime.Month, StartTime.Day, NightStart, 0, 0);
            DateTime tne = new DateTime(ShutTime.Year, ShutTime.Month, ShutTime.Day, NightEnd, 0, 0);
            if (tne <= ShutTime && tne >= StartTime)
            {
                MessageBox.Show("本机已包夜，不能再续费。");
                Close();

                return;
            }
            tne.AddDays(-1);
            if (tne <= ShutTime && tne >= StartTime)
            {
                MessageBox.Show("本机已包夜，不能再续费。");
                Close();

                return;
            }

            //if (tne < tns)
            //{
            //    tne += 24;
            //}
            //if ((StartTime.Hour >= tns && StartTime.Hour <= tne) || (StartTime.Hour + 24 >= tns && StartTime.Hour <= tne))
            //{
            //    MessageBox.Show("本机已包夜，不能再续费。");
            //    Close();

            //    return;
            //}
            //else
            //if ((StartTime.Hour <= tns && ShutTime.Hour >= tne) || (StartTime.Hour <= tns && ShutTime.Hour + 24 >= tne))
            //{
            //    MessageBox.Show("本机已包夜，不能再续费。");
            //    Close();

            //    return;
            //}
            //else
            
            //NightLong = tne - tns;
            int te = NightEnd;
            int ts = NightStart;
            if (te < ts) te += 24;
            NightLong = te - ts;

            TypeNameLabel.Text = "[" + TypeInfo["TypeName"] + "]";
            LVIPNo.Text = "会员账号: " + VIPNo;
            LStartTime.Text = "开机时间: " + StartTime.ToString();
            LShutTime.Text = "关机时间: " + ShutTime.ToString();

            // 续费时长最大时间
            if (NightStart > ShutTime.Hour)
            {
                BoxLastLong.Maximum = NightStart - ShutTime.Hour;
            }
            else
            {
                BoxLastLong.Maximum = (24 - ShutTime.Hour) + NightStart;
            }

            LBalance.Text = "会员余额: " + Convert.ToDouble(VIPInfo["Balance"]).ToString("0.00") + " 元";

            // 计算价格
            CalcPrice();
        }

        private void BoxLastLong_ValueChanged(object sender, EventArgs e)
        {
            CalcPrice();
        }

        private void IsNight_CheckedChanged(object sender, EventArgs e)
        {
            CalcPrice();

            BoxLastLong.Enabled = !IsNight.Checked;
        }

        private void BoxUseBalance_ValueChanged(object sender, EventArgs e)
        {
            CalcPrice();
        }

        private void Cancel_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void OK_Click(object sender, EventArgs e)
        {
            if (PriceWithBalance > Convert.ToDouble(BoxMoney.Value))
            {
                MessageBox.Show("金额不足！");
                return;
            }

            OrderData od = new OrderData();
            od.MachineNo = MachineNo;
            od.VIPNo = VIPNo;
            od.ShutTime = ShutTime.AddHours(LastLong);
            if (IsNight.Checked)
            {
                od.ShutTime = ShutTime.AddHours(LastLong + NightLong);
            }
            od.Money = PriceWithBalance;
            od.UseBalance = Convert.ToDouble(BoxUseBalance.Value);

            if (MER.ContinueTime(ExpNo, od))
            {
                MessageBox.Show("续费成功！");
                Close();
                return;
            }
            else
            {
                MessageBox.Show("系统错误，请稍后再试。");
                
                return;
            }
        }

        private void BoxMoney_ValueChanged(object sender, EventArgs e)
        {
            CalcPrice();
        }
    }
}
