using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;
using KTV.Model.DataRow;

namespace KTV.Model.DataLink
{
    #region 用户模型类
    class FrontDeskUserModel : ObjectModel
    {
        public FrontDeskUserModel()
        {
        }

        #region 私有的方法（将SqlDataReader中的数据填充到FrontDeskUserInfo）
        private IList<FrontDeskUserInfo> FillFrontDeskUserInfo(SqlDataReader dr)
        {
            List<FrontDeskUserInfo> list = new List<FrontDeskUserInfo>();
            while (dr.Read())
            {
                FrontDeskUserInfo FDUI = new FrontDeskUserInfo();

                FDUI["UID"] = Convert.ToInt32(dr["UID"]);
                FDUI["Username"] = dr["Username"].ToString();
                FDUI["Password"] = dr["Password"].ToString();
                FDUI["LoginTime"] = Convert.ToDateTime(dr["LoginTime"]);
                FDUI["Type"] = Convert.ToInt32(dr["Type"]);

                list.Add(FDUI);
            }

            return list;
        }
        #endregion

        #region 公共的方法（根据UID获取用户资料）
        public IList<FrontDeskUserInfo> GetUserInfo(int UID)
        {
            IList<FrontDeskUserInfo> list = null;

            try
            {
                SqlString = "SELECT * FROM FrontDeskUser WHERE UID = " + UID.ToString();
                Cmd.CommandText = SqlString;
                Conn.Open();

                SqlDataReader dr = Cmd.ExecuteReader();
                list = FillFrontDeskUserInfo(dr);

                dr.Close();
                Conn.Close();
            }
            catch(SqlException e)
            {
                /** 设置错误 */
                LastError = e.Message;
                return null;
            }

            return list;
        }
        #endregion

        #region 公共的方法（根据用户名获取用户资料）
        public IList<FrontDeskUserInfo> GetUserInfo(String Username)
        {
            IList<FrontDeskUserInfo> list = null;

            try
            {
                SqlString = "SELECT * FROM FrontDeskUser WHERE Username = '" + Username.ToString() + "'";
                Cmd.CommandText = SqlString;
                Conn.Open();

                SqlDataReader dr = Cmd.ExecuteReader();
                list = FillFrontDeskUserInfo(dr);

                dr.Close();
                Conn.Close();
            }
            catch (SqlException e)
            {
                /** 设置错误 */
                LastError = e.Message;
                return null;
            }

            return list;
        }
        #endregion

        #region 公共的方法（根据条件获取用户资料）
        public IList<FrontDeskUserInfo> GetUserInfo(String condition, bool bCondition)
        {
            if (!bCondition) return GetUserInfo(condition);

            IList<FrontDeskUserInfo> list = null;
            try
            {
                SqlString = "SELECT * FROM FrontDeskUser";
                if (condition != "") SqlString += (" WHERE " + condition);

                Cmd.CommandText = SqlString;
                Conn.Open();

                SqlDataReader dr = Cmd.ExecuteReader();
                list = FillFrontDeskUserInfo(dr);

                dr.Close();
                Conn.Close();
            }
            catch (SqlException e)
            {
                /** 设置错误 */
                LastError = e.Message;
                return null;
            }

            return list;
        }
        #endregion

        #region 公共的方法（修改用户资料）
        public String SetUserInfo(int UID, Dictionary<String, String> info)
        {
            SqlString = "UPDATE FrontDeskUser SET ";

            int cnt = 0;
            foreach (KeyValuePair<String, String> i in info)
            {
                if (cnt != 0) SqlString += ", ";
                SqlString += (i.Key + " = '" + i.Value + "' ");
                cnt++;
            }
            SqlString += "WHERE UID = " + UID;

            try
            {
                Cmd.CommandText = SqlString;
                Conn.Open();

                int count = Cmd.ExecuteNonQuery();
                Conn.Close();

                if (count == 0)
                {
                    return "数据没有任何改变。";
                }
            }
            catch (SqlException e)
            {
                Conn.Close();

                LastError = e.Message;
                return LastError;
            }

            return "";
        }
        #endregion

        #region 公共的方法（新建用户）
        public String CreateUser(String Username, String Password, int Type)
        {
            if (GetUserInfo(Username).Count() != 0)
            {
                return "已存在的用户名";
            }

            SqlString = "INSERT INTO FrontDeskUser(Username, Password, LoginTime, Type) VALUES(";
            SqlString += ("'" + Username + "', '" + Password + "', '" + DateTime.Now.ToString() + "', " + Type + ")");

            try
            {
                Cmd.CommandText = SqlString;
                Conn.Open();

                Cmd.ExecuteNonQuery();
                Conn.Close();
            }
            catch (SqlException e)
            {
                LastError = e.Message;
                return e.Message;
            }

            return "";
        }
        #endregion

        #region 公共的方法（删除用户）
        public bool DeleteUser(int UID)
        {
            SqlString = "DELETE FROM FrontDeskUser WHERE UID = " + UID.ToString();

            try
            {
                Cmd.CommandText = SqlString;
                Conn.Open();

                Cmd.ExecuteNonQuery();
                Conn.Close();
            }
            catch(SqlException e)
            {
                LastError = e.Message;
                return false;
            }

            return true;
        }
        #endregion
    }
    #endregion
}
