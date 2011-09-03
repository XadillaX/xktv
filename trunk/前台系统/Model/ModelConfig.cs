using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;

namespace 前台系统.Model
{
    class ModelConfig : ModelObject
    {
        public ModelConfig(SqlConnection conn) : base(conn)
        {
        }

        public String GetValue(String Key)
        {
            String query = "SELECT ConfigValue FROM Config WHERE ConfigKey = '" + Key + "'";

            OpenConn();
            SqlCommand cmd = new SqlCommand(query, conn);
            SqlDataReader dr = cmd.ExecuteReader();

            if (dr.Read())
            {
                String rst = dr["ConfigValue"].ToString();
                dr.Close();
                CloseConn();

                return rst;
            }
            else
            {
                dr.Close();
                CloseConn();
                return "";
            }
        }

        public int GetValueInt(String Key)
        {
            String rst = GetValue(Key);

            if (rst == "") return 0;
            else return Convert.ToInt32(rst);
        }

        public Double GetValueDouble(String Key)
        {
            String rst = GetValue(Key);

            if (rst == "") return 0;
            else return Convert.ToDouble(rst);
        }
    }
}
