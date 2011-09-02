using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;
using System.Windows.Forms;

namespace 前台系统.Model
{
    class ModelMachine : ModelObject
    {
        public ModelMachine(SqlConnection conn) : base(conn)
        {
        }

        // 获取包厢信息
        public SqlDataReader GetMachineInfo_CloseByYourself(String fields, String condition)
        {
            String query = "SELECT " + fields + " FROM Machine, MachineType WHERE Machine.TypeNo = MachineType.TypeNo";
            if(condition != "") query += (" AND " + condition);

            OpenConn();

            SqlDataReader dr;
            try
            {
                SqlCommand cmd = new SqlCommand(query, conn);
                dr = cmd.ExecuteReader();
            }
            catch (Exception e)
            {
                return null;
            }

            return dr;
        }

        public bool SetStatus(String status, String MachineNo)
        {
            // 更新语句
            String query = "UPDATE Machine SET Status = '" + status + "' WHERE MachineNo = '" + MachineNo + "'";

            OpenConn();
            try
            {
                SqlCommand cmd = new SqlCommand(query, conn);
                int count = cmd.ExecuteNonQuery();

                CloseConn();
                if (count == 0) return false;
                else return true;
            }
            catch (SqlException e)
            {
                MessageBox.Show(e.Message);

                CloseConn();
                return false;
            }
        }

        public bool SetStatus(String status, String[] MachineNo, int count)
        {
            if (count == 0) return false;

            // 更新语句
            String query = "UPDATE Machine SET Status = '" + status + "' WHERE MachineNo IN(";
            for (int i = 0; i < count - 1; i++)
            {
                query += ("'" + MachineNo[i] + "',  ");
            }
            query += ("'" + MachineNo[count - 1].ToString() + "')");

            OpenConn();
            try
            {
                SqlCommand cmd = new SqlCommand(query, conn);
                count = cmd.ExecuteNonQuery();

                CloseConn();
                if (count == 0) return false;
                else return true;
            }
            catch (SqlException e)
            {
                MessageBox.Show(e.Message);

                CloseConn();
                return false;
            }
        }
    }
}
