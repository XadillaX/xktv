using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;

namespace 前台系统.Model
{
    class ModelVIP : ModelObject
    {
        public ModelVIP(SqlConnection conn) : base(conn)
        {
        }

        public bool ChangeBalance(String VIPNo, Double Money)
        {
            String query = "UPDATE VIP SET Balance = Balance + " + Money.ToString() + " WHERE VIPNo = '" + VIPNo + "'";
            OpenConn();
            SqlCommand cmd = new SqlCommand(query, conn);
            int count = cmd.ExecuteNonQuery();
            CloseConn();

            return true;
        }

        public String RegVIP(String VIPNo, String VIPName, String VIPID, String VIPMobile, Double Balance)
        {
            if (VIPNo.Length != 10) return "会员卡号需10位。";
            Dictionary<String, String> tmp = GetVIPInfo(VIPNo);
            if (null != tmp) return "此卡号已存在！";

            String query = "INSERT INTO VIP(VIPNo, VIPName, VIPID, VIPMobile, Balance) VALUES(";
            query += ("'" + VIPNo + "', ");
            query += ("'" + VIPName + "', ");
            query += ("'" + VIPID + "', ");
            query += ("'" + VIPMobile + "', ");
            query += (Balance.ToString() + ")");

            try
            {
                OpenConn();
                SqlCommand cmd = new SqlCommand(query, conn);
                cmd.ExecuteNonQuery();
                CloseConn();
            }
            catch (SqlException e)
            {
                CloseConn();
                return e.Message;
            }

            return "";
        }

        // 获取单个VIP用户信息
        public Dictionary<String, String> GetVIPInfo(String VIPNo)
        {
            String query = "SELECT * FROM VIP WHERE VIPNo = '" + VIPNo + "'";

            OpenConn();
            SqlCommand cmd = new SqlCommand(query, conn);
            SqlDataReader dr = cmd.ExecuteReader();

            if (dr.Read())
            {
                Dictionary<String, String> Info = new Dictionary<string,string>();
                Info["VIPNo"] = dr["VIPNo"].ToString();
                Info["VIPName"] = dr["VIPName"].ToString();
                Info["VIPID"] = dr["VIPID"].ToString();
                Info["VIPMobile"] = dr["VIPMobile"].ToString();
                Info["Balance"] = dr["Balance"].ToString();
                Info["CurExp"] = dr["CurExp"].ToString();
                Info["TotExp"] = dr["TotExp"].ToString();

                dr.Close();
                CloseConn();

                return Info;
            }
            else
            {
                dr.Close();
                CloseConn();
                return null;
            }
        }
    }
}
