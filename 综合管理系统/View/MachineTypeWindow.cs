using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using KTV.Model.DataLink;
using KTV.Model.DataRow;
using KTV.Controller;

namespace KTV.View
{
    public partial class MachineTypeWindow : Form
    {
        private IList<KTV.Model.DataRow.MachineTypeInfo> List;
        private int CurIdx = -1;
        private bool bAdd = false;

        public MachineTypeWindow(bool isAdd)
        {
            InitializeComponent();

            bAdd = isAdd;
        }

        private void MachineTypeWindow_Load(object sender, EventArgs e)
        {
            List = MachineTypeCtrl.GetMachineTypeList("");

            for (int i = 0; i < List.Count(); i++) machineTypeInfoBindingSource.Add(List[i]);
            DataGrid.Update();

            if (List.Count() > 0) CurIdx = 0;
            if (true == bAdd)
            {
                button1.Text = "添加(&A)";
                button2.Visible = false;
                TypeNo.Enabled = true;
            }
        }

        private void DataGrid_CellMouseClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            if (e.RowIndex < 0) return;
            else CurIdx = e.RowIndex;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (!bAdd)
            {
                if (CurIdx == -1)
                {
                    MessageBox.Show("你未选中任何包厢类型！");
                    return;
                }

                Double[] Price = new Double[6];
                Price[0] = Convert.ToDouble(p0.Value); Price[1] = Convert.ToDouble(p1.Value); Price[2] = Convert.ToDouble(p2.Value);
                Price[3] = Convert.ToDouble(p3.Value); Price[4] = Convert.ToDouble(p4.Value); Price[5] = Convert.ToDouble(p5.Value);

                String result = MachineTypeCtrl.ModifyMachineType(TypeNo.Text, TypeName.Text, Price);
                if ("" == result)
                {
                    List[CurIdx] = MachineTypeCtrl.GetMachineTypeList("TypeNo = '" + TypeNo.Text + "'")[0];
                    machineTypeInfoBindingSource[CurIdx] = List[CurIdx];
                    MessageBox.Show("修改成功！");
                    return;
                }
                else
                {
                    MessageBox.Show("错误：" + result);
                    return;
                }
            }
            else
            {
                Double[] Price = new Double[6];
                Price[0] = Convert.ToDouble(p0.Value); Price[1] = Convert.ToDouble(p1.Value); Price[2] = Convert.ToDouble(p2.Value);
                Price[3] = Convert.ToDouble(p3.Value); Price[4] = Convert.ToDouble(p4.Value); Price[5] = Convert.ToDouble(p5.Value);

                String result = MachineTypeCtrl.AddMachineType(TypeNo.Text, TypeName.Text, Price);
                if ("" == result)
                {
                    List.Add(MachineTypeCtrl.GetMachineTypeList("TypeNo = '" + TypeNo.Text + "'")[0]);
                    machineTypeInfoBindingSource.Add(List[List.Count() - 1]);
                    MessageBox.Show("添加成功！");
                    return;
                }
                else
                {
                    MessageBox.Show("错误：" + result);
                    return;
                }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {

        }
    }
}
