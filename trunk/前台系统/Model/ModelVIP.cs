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
