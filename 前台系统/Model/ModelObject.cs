using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;
using System.Windows.Forms;

namespace 前台系统.Model
{
    class ModelObject
    {
        protected SqlConnection conn;

        public ModelObject(SqlConnection _conn)
        {
            //conn = _conn;
            conn = new SqlConnection(_conn.ConnectionString);
        }

        public void OpenConn()
        {
            try
            {
                conn.Open();
            }
            catch (Exception e)
            {
                MessageBox.Show("数据库连接打开错误！");
                Application.Exit();
            }
        }

        public void CloseConn()
        {
            try
            {
                conn.Close();
            }
            catch (Exception e)
            {
                MessageBox.Show("数据库连接关闭错误！");
                Application.Exit();
            }
        }

        public String GetPageSQL(string fields, string table, string condition, string order, int page, int pageSize)
        {
            string rst = "SELECT ROW_NUMBER() OVER ";
            if(order != "")
            {
                rst += ("(ORDER BY " + order + ") ");
            }
            rst += ("AS RowNumber, " + fields + " FROM " + table);
            if(condition != "")
            {
                rst += (" WHERE " + condition);
            }

            string rtn = "SELECT TOP ";
            rtn += pageSize.ToString();
            rtn += " ";
            rtn += (fields + "\nFROM\n    (\n    ");
            rtn += (rst + "\n    ) A\nWHERE RowNumber > ");
            rtn += (pageSize * (page - 1)).ToString();

            return rtn;
        }
    }
}
