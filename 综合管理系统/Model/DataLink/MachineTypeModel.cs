using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;
using KTV.Model.DataRow;

namespace KTV.Model.DataLink
{
    class MachineTypeModel : Object
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
    }
}
