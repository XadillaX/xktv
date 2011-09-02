using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;
using System.Collections;
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
            catch (SqlException e)
            {
                MessageBox.Show(e.Message);
                return null;
            }

            return dr;
        }

        // 设置包厢状态
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

        // 设置包厢状态
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

        // 获取包厢类型信息
        public Dictionary<String, String>[] GetMachineType(String condition)
        {
            // 查询语句
            String query = "SELECT * FROM MachineType";
            if (condition != "") query += (" WHERE " + condition);

            OpenConn();
            SqlDataReader dr;
            try
            {
                SqlCommand cmd = new SqlCommand(query, conn);
                dr = cmd.ExecuteReader();
            }
            catch (SqlException e)
            {
                MessageBox.Show(e.Message);

                CloseConn();
                return null;
            }

            ArrayList Temp = new ArrayList();
            while (dr.Read())
            {
                Dictionary<String, String> dict = new Dictionary<string, string>();

                dict["TypeNo"] = dr["TypeNo"].ToString();
                dict["TypeName"] = dr["TypeName"].ToString();

                // 价格
                String[] Price = dr["Price"].ToString().Split('|');
                for (int i = 0; i < Price.Count(); i++)
                {
                    dict["Price" + i.ToString()] = Price[i].ToString();
                }

                Temp.Add(dict);
            }

            Dictionary<String, String>[] Result = new Dictionary<string, string>[Temp.Count];
            for (int i = 0; i < Temp.Count; i++) Result[i] = (Dictionary<String, String>)Temp[i];

            dr.Close();
            CloseConn();
            return Result;
        }
    }
}
