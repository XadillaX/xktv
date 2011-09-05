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
            if (dr.Read())
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
    }
    #endregion
}
