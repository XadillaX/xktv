using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;
using 前台系统.Class;
using System.Windows.Forms;

namespace 前台系统.Model
{
    class ModelExpRecord : ModelObject
    {
        public ModelExpRecord(SqlConnection conn) : base(conn)
        {
        }

        public bool ContinueTime(int ExpNo, OrderData od)
        {
            ModelConfig MC = new ModelConfig(conn);
            int Rate = Convert.ToInt32(MC.GetValue("CreditRate"));

            String query = "UPDATE ExpRecord SET Price = Price + " + od.Money.ToString() + " WHERE ExpNo = " + ExpNo.ToString();
            OpenConn();

            // 事务
            SqlTransaction Trans = conn.BeginTransaction();
            SqlCommand cmd = new SqlCommand(query, conn, Trans);

            try
            {
                int count = cmd.ExecuteNonQuery();
                if (count == 0)
                {
                    Trans.Rollback();
                    CloseConn();
                    return false;
                }

                if (od.VIPNo != "0000000000")
                {
                    query = "UPDATE VIP SET Balance = Balance - " + od.UseBalance.ToString();
                    query += (", CurExp = CurExp + " + ((int)(od.Money / Rate)).ToString());
                    query += (" WHERE VIPNo = '" + od.VIPNo + "'");
                    cmd.CommandText = query;

                    count = cmd.ExecuteNonQuery();
                    if (count == 0)
                    {
                        Trans.Rollback();
                        CloseConn();
                        return false;
                    }
                }

                query = "UPDATE Machine SET ShutTime = '" + od.ShutTime.ToString() + "'";
                query += (" WHERE MachineNo = '" + od.MachineNo + "'");
                cmd.CommandText = query;

                count = cmd.ExecuteNonQuery();
                if (count == 0)
                {
                    Trans.Rollback();
                    CloseConn();
                    return false;
                }

                Trans.Commit();
                CloseConn();
            }
            catch (SqlException e)
            {
                MessageBox.Show(e.Message);

                Trans.Rollback();
                CloseConn();

                return false;
            }

            return true;
        }

        public RecordInfo GetRecordInfo(int ExpNo)
        {
            String query = "SELECT * FROM ExpRecord WHERE ExpNo = " + ExpNo.ToString();

            OpenConn();
            SqlCommand cmd = new SqlCommand(query, conn);
            SqlDataReader dr = cmd.ExecuteReader();
            if (!dr.Read())
            {
                dr.Close();
                CloseConn();

                return null;
            }

            RecordInfo info = new RecordInfo();
            info.ExpNo = ExpNo;
            info.ExpTime = Convert.ToDateTime(dr["ExpTime"].ToString());
            info.MachineNo = dr["MachineNo"].ToString();
            info.Price = Convert.ToDouble(dr["Price"].ToString());
            info.UID = Convert.ToInt32(dr["UID"].ToString());
            info.VIPNo = dr["VIPNo"].ToString();

            dr.Close();
            CloseConn();

            return info;
        }
    }
}
