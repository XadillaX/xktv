using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;

namespace KTV.Model
{
    #region 数据库连接静态类
    class GetConn
    {
        #region 公开的属性 （获取连接字符串）
        public static string ConnectionString
        {
            get
            {
                return "UID=sa; pwd=; database=ktv; server=localhost";
            }
        }
        #endregion

        #region 公开的属性 （获取连接字符串 ToString() 形式）
        public static string ToString()
        {
            return GetConn.ConnectionString;
        }
        #endregion

        #region 公开的属性 （获取连接对象）
        public static SqlConnection Connection
        {
            get
            {
                return new SqlConnection(GetConn.ConnectionString);
            }
        }
        #endregion
    }
    #endregion
}
