using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using KTV.Model.DataLink;
using KTV.Model.DataRow;

namespace KTV.Controller
{
    class MachineTypeCtrl : ObjectCtrl
    {
        #region 公共的方法（获取包厢类型列表）
        public static IList<MachineTypeInfo> GetMachineTypeList(String condition)
        {
            MachineTypeModel MTM = new MachineTypeModel();
            return MTM.GetMachineType(condition);
        }
        #endregion

        #region 公共的方法（修改包厢类型）
        public static String ModifyMachineType(String TypeNo, String TypeName, Double[] Price)
        {
            MachineTypeInfo MTI = new MachineTypeInfo();
            MTI.TypeNo = TypeNo;
            MTI.TypeName = TypeName;

            String tmp = "";
            for(int i = 0; i < 6; i++) tmp += (Price[i].ToString() + "|");
            MTI.Price = tmp;

            MachineTypeModel MTM = new MachineTypeModel();
            return MTM.ModifyMachineType(MTI);
        }
        #endregion

        #region 公共的方法（删除包厢类型）
        public static String DeleteMachineType(String TypeNo)
        {
            MachineTypeModel MTM = new MachineTypeModel();
            return MTM.DeleteMachineType(TypeNo);
        }
        #endregion

        #region 公共的方法（添加包厢类型）
        public static String AddMachineType(String TypeNo, String TypeName, Double[] Price)
        {
            MachineTypeModel MTM = new MachineTypeModel();

            TypeNo = TypeNo.Trim();
            TypeName = TypeName.Trim();

            if (TypeNo.Length != 5)
            {
                return "类型编号的长度必须为5。";
            }

            MachineTypeInfo MTI = new MachineTypeInfo();
            MTI.TypeNo = TypeNo;
            MTI.TypeName = TypeName;
            if (MTM.GetMachineType("TypeNo = '" + TypeNo + "' OR TypeName = '" + TypeName + "'").Count() != 0)
            {
                return "已存在的包厢类型。";
            }

            String tmp = "";
            for (int i = 0; i < 6; i++) tmp += (Price[i].ToString() + "|");
            MTI.Price = tmp;

            return MTM.AddMachineType(MTI);
        }
        #endregion
    }
}
