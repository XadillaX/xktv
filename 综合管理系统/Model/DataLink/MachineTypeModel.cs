using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;
using KTV.Model.DataRow;

namespace KTV.Model.DataLink
{
    class MachineTypeModel : ObjectModel
    {
        public MachineTypeModel()
        {
        }

        #region 私有的方法（将SqlDataReader中的数据填充到MachineTypeInfo）
        private IList<MachineTypeInfo> FillMachineTypeInfo(SqlDataReader dr)
        {
            List<MachineTypeInfo> list = new List<MachineTypeInfo>();
            while (dr.Read())
            {
                MachineTypeInfo MTI = new MachineTypeInfo();

                MTI.TypeNo = dr["TypeNo"].ToString();
                MTI.TypeName = dr["TypeName"].ToString();
                MTI.Price = dr["Price"].ToString();

                list.Add(MTI);
            }

            return list;
        }
        #endregion

        #region 公共的方法（删除包厢）
        public String DeleteMachineType(String TypeNo)
        {
            SqlString = "DELETE FROM MachineType WHERE TypeNo = '" + TypeNo + "'";

            Cmd.CommandText = SqlString;

            try
            {
                Conn.Open();
                Cmd.ExecuteNonQuery();
                Conn.Close();
            }
            catch (SqlException e)
            {
                LastError = e.Message;
                Conn.Close();

                return LastError;
            }

            return "";
        }
        #endregion

        #region 公共的方法（修改包厢类型）
        public String ModifyMachineType(MachineTypeInfo MTI)
        {
            SqlString = "UPDATE MachineType SET TypeName = '" + MTI.TypeName + "', Price = '" + MTI.Price + "'";
            SqlString += (" WHERE TypeNo = '" + MTI.TypeNo + "'");

            Cmd.CommandText = SqlString;
            try
            {
                Conn.Open();
                Cmd.ExecuteNonQuery();
                Conn.Close();
            }
            catch (SqlException e)
            {
                LastError = e.Message;
                Conn.Close();

                return null;
            }

            return "";
        }
        #endregion

        #region 公共的方法（获取包厢类型列表）
        public IList<MachineTypeInfo> GetMachineType(String condition)
        {
            IList<MachineTypeInfo> list;
            SqlString = "SELECT * FROM MachineType";
            if("" != condition) SqlString += (" WHERE " + condition);
            Cmd.CommandText = SqlString;

            try
            {
                Conn.Open();
                SqlDataReader dr = Cmd.ExecuteReader();
                list = FillMachineTypeInfo(dr);
                dr.Close();
                Conn.Close();
            }
            catch (SqlException e)
            {
                LastError = e.Message;
                Conn.Close();

                return null;
            }

            return list;
        }
        #endregion

        #region 公共的方法（添加包厢类型）
        public String AddMachineType(MachineTypeInfo MTI)
        {
            SqlString = "INSERT INTO MachineType(TypeNo, TypeName, Price) VALUES(";
            SqlString += ("'" + MTI.TypeNo + "', ");
            SqlString += ("'" + MTI.TypeName + "', ");
            SqlString += ("'" + MTI.Price + "')");

            Cmd.CommandText = SqlString;
            try
            {
                Conn.Open();
                Cmd.ExecuteNonQuery();
                Conn.Close();
            }
            catch (SqlException e)
            {
                LastError = e.Message;
                Conn.Close();

                return LastErr;
            }

            return "";
        }
        #endregion
    }
}
