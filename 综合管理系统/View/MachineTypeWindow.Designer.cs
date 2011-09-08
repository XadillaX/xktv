namespace KTV.View
{
    partial class MachineTypeWindow
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MachineTypeWindow));
            this.DataGrid = new System.Windows.Forms.DataGridView();
            this.machineTypeInfoBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.typeNoDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.typeNameDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.priceWeekdaysDayDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.priceWeekdaysGoldDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.priceWeekdaysNightDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.priceWeekendDayDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.priceWeekendGoldDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.priceWeekendNightDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            ((System.ComponentModel.ISupportInitialize)(this.DataGrid)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.machineTypeInfoBindingSource)).BeginInit();
            this.SuspendLayout();
            // 
            // DataGrid
            // 
            this.DataGrid.AutoGenerateColumns = false;
            this.DataGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.DataGrid.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.typeNoDataGridViewTextBoxColumn,
            this.typeNameDataGridViewTextBoxColumn,
            this.priceWeekdaysDayDataGridViewTextBoxColumn,
            this.priceWeekdaysGoldDataGridViewTextBoxColumn,
            this.priceWeekdaysNightDataGridViewTextBoxColumn,
            this.priceWeekendDayDataGridViewTextBoxColumn,
            this.priceWeekendGoldDataGridViewTextBoxColumn,
            this.priceWeekendNightDataGridViewTextBoxColumn});
            this.DataGrid.DataSource = this.machineTypeInfoBindingSource;
            this.DataGrid.Location = new System.Drawing.Point(12, 12);
            this.DataGrid.Name = "DataGrid";
            this.DataGrid.RowTemplate.Height = 23;
            this.DataGrid.Size = new System.Drawing.Size(864, 316);
            this.DataGrid.TabIndex = 0;
            // 
            // machineTypeInfoBindingSource
            // 
            this.machineTypeInfoBindingSource.DataSource = typeof(KTV.Model.DataRow.MachineTypeInfo);
            // 
            // typeNoDataGridViewTextBoxColumn
            // 
            this.typeNoDataGridViewTextBoxColumn.DataPropertyName = "TypeNo";
            this.typeNoDataGridViewTextBoxColumn.HeaderText = "类型编号";
            this.typeNoDataGridViewTextBoxColumn.Name = "typeNoDataGridViewTextBoxColumn";
            // 
            // typeNameDataGridViewTextBoxColumn
            // 
            this.typeNameDataGridViewTextBoxColumn.DataPropertyName = "TypeName";
            this.typeNameDataGridViewTextBoxColumn.HeaderText = "类型名";
            this.typeNameDataGridViewTextBoxColumn.Name = "typeNameDataGridViewTextBoxColumn";
            // 
            // priceWeekdaysDayDataGridViewTextBoxColumn
            // 
            this.priceWeekdaysDayDataGridViewTextBoxColumn.DataPropertyName = "PriceWeekdaysDay";
            this.priceWeekdaysDayDataGridViewTextBoxColumn.HeaderText = "工作日白天";
            this.priceWeekdaysDayDataGridViewTextBoxColumn.Name = "priceWeekdaysDayDataGridViewTextBoxColumn";
            // 
            // priceWeekdaysGoldDataGridViewTextBoxColumn
            // 
            this.priceWeekdaysGoldDataGridViewTextBoxColumn.DataPropertyName = "PriceWeekdaysGold";
            this.priceWeekdaysGoldDataGridViewTextBoxColumn.HeaderText = "工作日黄金时段";
            this.priceWeekdaysGoldDataGridViewTextBoxColumn.Name = "priceWeekdaysGoldDataGridViewTextBoxColumn";
            // 
            // priceWeekdaysNightDataGridViewTextBoxColumn
            // 
            this.priceWeekdaysNightDataGridViewTextBoxColumn.DataPropertyName = "PriceWeekdaysNight";
            this.priceWeekdaysNightDataGridViewTextBoxColumn.HeaderText = "工作日包夜";
            this.priceWeekdaysNightDataGridViewTextBoxColumn.Name = "priceWeekdaysNightDataGridViewTextBoxColumn";
            // 
            // priceWeekendDayDataGridViewTextBoxColumn
            // 
            this.priceWeekendDayDataGridViewTextBoxColumn.DataPropertyName = "PriceWeekendDay";
            this.priceWeekendDayDataGridViewTextBoxColumn.HeaderText = "周末白天";
            this.priceWeekendDayDataGridViewTextBoxColumn.Name = "priceWeekendDayDataGridViewTextBoxColumn";
            // 
            // priceWeekendGoldDataGridViewTextBoxColumn
            // 
            this.priceWeekendGoldDataGridViewTextBoxColumn.DataPropertyName = "PriceWeekendGold";
            this.priceWeekendGoldDataGridViewTextBoxColumn.HeaderText = "周末黄金时段";
            this.priceWeekendGoldDataGridViewTextBoxColumn.Name = "priceWeekendGoldDataGridViewTextBoxColumn";
            // 
            // priceWeekendNightDataGridViewTextBoxColumn
            // 
            this.priceWeekendNightDataGridViewTextBoxColumn.DataPropertyName = "PriceWeekendNight";
            this.priceWeekendNightDataGridViewTextBoxColumn.HeaderText = "周末包夜";
            this.priceWeekendNightDataGridViewTextBoxColumn.Name = "priceWeekendNightDataGridViewTextBoxColumn";
            // 
            // MachineTypeWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(888, 442);
            this.Controls.Add(this.DataGrid);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "MachineTypeWindow";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "包厢类型";
            ((System.ComponentModel.ISupportInitialize)(this.DataGrid)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.machineTypeInfoBindingSource)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView DataGrid;
        private System.Windows.Forms.BindingSource machineTypeInfoBindingSource;
        private System.Windows.Forms.DataGridViewTextBoxColumn typeNoDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn typeNameDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn priceWeekdaysDayDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn priceWeekdaysGoldDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn priceWeekdaysNightDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn priceWeekendDayDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn priceWeekendGoldDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn priceWeekendNightDataGridViewTextBoxColumn;
    }
}