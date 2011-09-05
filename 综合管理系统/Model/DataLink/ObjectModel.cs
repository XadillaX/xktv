using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;

namespace KTV.Model.DataLink
{
    #region 模型基类
    class ObjectModel
    {
        protected SqlConnection Conn = null;
        protected SqlCommand Cmd = null;
        protected String SqlString = "";
        protected String LastError = "";

        #region 公共的方法（构造函数）
        public ObjectModel()
        {
            Conn = new SqlConnection(GetConn.ConnectionString);
            Cmd = new SqlCommand();
            Cmd.Connection = Conn;
            Cmd.CommandType = System.Data.CommandType.Text;
        }
        #endregion

        #region 公共的方法（获取分页SQL字符串）
        public String GetPageSQL(String fields, String table, String condition, String order, int page, int pageSize)
        {
            String rst = "SELECT ROW_NUMBER() OVER ";
            if (order != "")
            {
                rst += ("(ORDER BY " + order + ") ");
            }
            rst += ("AS RowNumber, " + fields + " FROM " + table);
            if (condition != "")
            {
                rst += (" WHERE " + condition);
            }

            String rtn = "SELECT TOP ";
            rtn += pageSize.ToString();
            rtn += " ";
            rtn += (fields + "\nFROM\n    (\n    ");
            rtn += (rst + "\n    ) A\nWHERE RowNumber > ");
            rtn += (pageSize * (page - 1)).ToString();

            return rtn;
        }
        #endregion

        #region 公共的属性（最后一条SQL语句）
        public String LastSql
        {
            get
            {
                return SqlString;
            }
        }
        #endregion

        #region 公共的属性（最后一次错误）
        public String LastErr
        {
            get
            {
                return LastError;
            }
        }
        #endregion
    }
    #endregion
}
