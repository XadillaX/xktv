using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;

namespace 前台系统.Model
{
    class ModelUser : ModelObject
    {
        public ModelUser(SqlConnection conn) : base(conn)
        {
        }

        public int GetUID(String username)
        {
            string query = "SELECT UID FROM FrontDeskUser WHERE Username = '" + username + "'";

            OpenConn();
            SqlCommand cmd = new SqlCommand(query, conn);
            SqlDataReader dr = cmd.ExecuteReader();

            if (dr.Read())
            {
                int uid = Convert.ToInt32(dr["UID"].ToString());
                dr.Close();
                CloseConn();

                return uid;
            }
            else
            {
                dr.Close();
                CloseConn();

                return -1;
            }
        }

        public int Login(String username, String password, int type)
        {
            // 查询语句
            String query = "SELECT * FROM FrontDeskUser WHERE Username = '" + username +
                "' AND Password = '" + password + "'";

            // 打开查询
            OpenConn();
            SqlCommand cmd = new SqlCommand(query, conn);
            SqlDataReader dr = cmd.ExecuteReader();

            if (dr.Read())
            {
                if (Convert.ToInt32(dr["Type"]) < type)
                {
                    dr.Close();
                    CloseConn();

                    // 权限不足
                    return -2;
                }

                int UID = Convert.ToInt32(dr["UID"]);

                // 返回用户编号
                dr.Close();
                CloseConn();
                return UID;
            }
            else
            {
                dr.Close();
                CloseConn();

                // 用户名密码错误
                return -1;
            }
        }
    }
}
