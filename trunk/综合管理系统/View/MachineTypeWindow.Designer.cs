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
            this.label1 = new System.Windows.Forms.Label();
            this.TypeNo = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.TypeName = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.p0 = new System.Windows.Forms.NumericUpDown();
            this.p1 = new System.Windows.Forms.NumericUpDown();
            this.label4 = new System.Windows.Forms.Label();
            this.p2 = new System.Windows.Forms.NumericUpDown();
            this.label5 = new System.Windows.Forms.Label();
            this.p5 = new System.Windows.Forms.NumericUpDown();
            this.label6 = new System.Windows.Forms.Label();
            this.p4 = new System.Windows.Forms.NumericUpDown();
            this.label7 = new System.Windows.Forms.Label();
            this.p3 = new System.Windows.Forms.NumericUpDown();
            this.label8 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
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
            ((System.ComponentModel.ISupportInitialize)(this.p0)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.p1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.p2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.p5)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.p4)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.p3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.machineTypeInfoBindingSource)).BeginInit();
            this.SuspendLayout();
            // 
            // DataGrid
            // 
            this.DataGrid.AllowUserToAddRows = false;
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
            this.DataGrid.MultiSelect = false;
            this.DataGrid.Name = "DataGrid";
            this.DataGrid.ReadOnly = true;
            this.DataGrid.RowTemplate.Height = 23;
            this.DataGrid.Size = new System.Drawing.Size(864, 316);
            this.DataGrid.TabIndex = 0;
            this.DataGrid.CellMouseClick += new System.Windows.Forms.DataGridViewCellMouseEventHandler(this.DataGrid_CellMouseClick);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 350);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(59, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "类型编号:";
            // 
            // TypeNo
            // 
            this.TypeNo.DataBindings.Add(new System.Windows.Forms.Binding("Text", this.machineTypeInfoBindingSource, "TypeNo", true, System.Windows.Forms.DataSourceUpdateMode.Never));
            this.TypeNo.Enabled = false;
            this.TypeNo.Location = new System.Drawing.Point(77, 347);
            this.TypeNo.Name = "TypeNo";
            this.TypeNo.Size = new System.Drawing.Size(132, 21);
            this.TypeNo.TabIndex = 2;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(14, 385);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(59, 12);
            this.label2.TabIndex = 3;
            this.label2.Text = "类 型 名:";
            // 
            // TypeName
            // 
            this.TypeName.DataBindings.Add(new System.Windows.Forms.Binding("Text", this.machineTypeInfoBindingSource, "TypeName", true, System.Windows.Forms.DataSourceUpdateMode.Never));
            this.TypeName.Location = new System.Drawing.Point(77, 382);
            this.TypeName.Name = "TypeName";
            this.TypeName.Size = new System.Drawing.Size(132, 21);
            this.TypeName.TabIndex = 4;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(250, 350);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(71, 12);
            this.label3.TabIndex = 5;
            this.label3.Text = "工作日白天:";
            // 
            // p0
            // 
            this.p0.DataBindings.Add(new System.Windows.Forms.Binding("Value", this.machineTypeInfoBindingSource, "PriceWeekdaysDay", true, System.Windows.Forms.DataSourceUpdateMode.Never));
            this.p0.DecimalPlaces = 2;
            this.p0.Location = new System.Drawing.Point(327, 347);
            this.p0.Maximum = new decimal(new int[] {
            1000000000,
            0,
            0,
            0});
            this.p0.Name = "p0";
            this.p0.Size = new System.Drawing.Size(72, 21);
            this.p0.TabIndex = 6;
            // 
            // p1
            // 
            this.p1.DataBindings.Add(new System.Windows.Forms.Binding("Value", this.machineTypeInfoBindingSource, "PriceWeekdaysGold", true, System.Windows.Forms.DataSourceUpdateMode.Never));
            this.p1.DecimalPlaces = 2;
            this.p1.Location = new System.Drawing.Point(504, 348);
            this.p1.Maximum = new decimal(new int[] {
            1000000000,
            0,
            0,
            0});
            this.p1.Name = "p1";
            this.p1.Size = new System.Drawing.Size(72, 21);
            this.p1.TabIndex = 8;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(427, 351);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(71, 12);
            this.label4.TabIndex = 7;
            this.label4.Text = "工作日黄金:";
            // 
            // p2
            // 
            this.p2.DataBindings.Add(new System.Windows.Forms.Binding("Value", this.machineTypeInfoBindingSource, "PriceWeekdaysNight", true, System.Windows.Forms.DataSourceUpdateMode.Never));
            this.p2.DecimalPlaces = 2;
            this.p2.Location = new System.Drawing.Point(682, 349);
            this.p2.Maximum = new decimal(new int[] {
            1000000000,
            0,
            0,
            0});
            this.p2.Name = "p2";
            this.p2.Size = new System.Drawing.Size(72, 21);
            this.p2.TabIndex = 10;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(605, 352);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(71, 12);
            this.label5.TabIndex = 9;
            this.label5.Text = "工作日包夜:";
            // 
            // p5
            // 
            this.p5.DataBindings.Add(new System.Windows.Forms.Binding("Value", this.machineTypeInfoBindingSource, "PriceWeekendNight", true, System.Windows.Forms.DataSourceUpdateMode.Never));
            this.p5.DecimalPlaces = 2;
            this.p5.Location = new System.Drawing.Point(682, 382);
            this.p5.Maximum = new decimal(new int[] {
            1000000000,
            0,
            0,
            0});
            this.p5.Name = "p5";
            this.p5.Size = new System.Drawing.Size(72, 21);
            this.p5.TabIndex = 16;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(605, 385);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(71, 12);
            this.label6.TabIndex = 15;
            this.label6.Text = "周  末包夜:";
            // 
            // p4
            // 
            this.p4.DataBindings.Add(new System.Windows.Forms.Binding("Value", this.machineTypeInfoBindingSource, "PriceWeekendGold", true, System.Windows.Forms.DataSourceUpdateMode.Never));
            this.p4.DecimalPlaces = 2;
            this.p4.Location = new System.Drawing.Point(504, 381);
            this.p4.Maximum = new decimal(new int[] {
            1000000000,
            0,
            0,
            0});
            this.p4.Name = "p4";
            this.p4.Size = new System.Drawing.Size(72, 21);
            this.p4.TabIndex = 14;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(427, 384);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(71, 12);
            this.label7.TabIndex = 13;
            this.label7.Text = "周  末黄金:";
            // 
            // p3
            // 
            this.p3.DataBindings.Add(new System.Windows.Forms.Binding("Value", this.machineTypeInfoBindingSource, "PriceWeekendDay", true, System.Windows.Forms.DataSourceUpdateMode.Never));
            this.p3.DecimalPlaces = 2;
            this.p3.Location = new System.Drawing.Point(327, 380);
            this.p3.Maximum = new decimal(new int[] {
            1000000000,
            0,
            0,
            0});
            this.p3.Name = "p3";
            this.p3.Size = new System.Drawing.Size(72, 21);
            this.p3.TabIndex = 12;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(250, 383);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(71, 12);
            this.label8.TabIndex = 11;
            this.label8.Text = "周  末白天:";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(801, 348);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 17;
            this.button1.Text = "修改(&M)";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(801, 381);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 18;
            this.button2.Text = "删除(&D)";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
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
            this.typeNoDataGridViewTextBoxColumn.ReadOnly = true;
            this.typeNoDataGridViewTextBoxColumn.Width = 80;
            // 
            // typeNameDataGridViewTextBoxColumn
            // 
            this.typeNameDataGridViewTextBoxColumn.DataPropertyName = "TypeName";
            this.typeNameDataGridViewTextBoxColumn.HeaderText = "类型名";
            this.typeNameDataGridViewTextBoxColumn.Name = "typeNameDataGridViewTextBoxColumn";
            this.typeNameDataGridViewTextBoxColumn.ReadOnly = true;
            // 
            // priceWeekdaysDayDataGridViewTextBoxColumn
            // 
            this.priceWeekdaysDayDataGridViewTextBoxColumn.DataPropertyName = "PriceWeekdaysDay";
            this.priceWeekdaysDayDataGridViewTextBoxColumn.HeaderText = "工作日白天";
            this.priceWeekdaysDayDataGridViewTextBoxColumn.Name = "priceWeekdaysDayDataGridViewTextBoxColumn";
            this.priceWeekdaysDayDataGridViewTextBoxColumn.ReadOnly = true;
            // 
            // priceWeekdaysGoldDataGridViewTextBoxColumn
            // 
            this.priceWeekdaysGoldDataGridViewTextBoxColumn.DataPropertyName = "PriceWeekdaysGold";
            this.priceWeekdaysGoldDataGridViewTextBoxColumn.HeaderText = "工作日黄金时段";
            this.priceWeekdaysGoldDataGridViewTextBoxColumn.Name = "priceWeekdaysGoldDataGridViewTextBoxColumn";
            this.priceWeekdaysGoldDataGridViewTextBoxColumn.ReadOnly = true;
            this.priceWeekdaysGoldDataGridViewTextBoxColumn.Width = 120;
            // 
            // priceWeekdaysNightDataGridViewTextBoxColumn
            // 
            this.priceWeekdaysNightDataGridViewTextBoxColumn.DataPropertyName = "PriceWeekdaysNight";
            this.priceWeekdaysNightDataGridViewTextBoxColumn.HeaderText = "工作日包夜";
            this.priceWeekdaysNightDataGridViewTextBoxColumn.Name = "priceWeekdaysNightDataGridViewTextBoxColumn";
            this.priceWeekdaysNightDataGridViewTextBoxColumn.ReadOnly = true;
            // 
            // priceWeekendDayDataGridViewTextBoxColumn
            // 
            this.priceWeekendDayDataGridViewTextBoxColumn.DataPropertyName = "PriceWeekendDay";
            this.priceWeekendDayDataGridViewTextBoxColumn.HeaderText = "周末白天";
            this.priceWeekendDayDataGridViewTextBoxColumn.Name = "priceWeekendDayDataGridViewTextBoxColumn";
            this.priceWeekendDayDataGridViewTextBoxColumn.ReadOnly = true;
            // 
            // priceWeekendGoldDataGridViewTextBoxColumn
            // 
            this.priceWeekendGoldDataGridViewTextBoxColumn.DataPropertyName = "PriceWeekendGold";
            this.priceWeekendGoldDataGridViewTextBoxColumn.HeaderText = "周末黄金时段";
            this.priceWeekendGoldDataGridViewTextBoxColumn.Name = "priceWeekendGoldDataGridViewTextBoxColumn";
            this.priceWeekendGoldDataGridViewTextBoxColumn.ReadOnly = true;
            // 
            // priceWeekendNightDataGridViewTextBoxColumn
            // 
            this.priceWeekendNightDataGridViewTextBoxColumn.DataPropertyName = "PriceWeekendNight";
            this.priceWeekendNightDataGridViewTextBoxColumn.HeaderText = "周末包夜";
            this.priceWeekendNightDataGridViewTextBoxColumn.Name = "priceWeekendNightDataGridViewTextBoxColumn";
            this.priceWeekendNightDataGridViewTextBoxColumn.ReadOnly = true;
            // 
            // MachineTypeWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(888, 442);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.p5);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.p4);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.p3);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.p2);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.p1);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.p0);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.TypeName);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.TypeNo);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.DataGrid);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "MachineTypeWindow";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "包厢类型";
            this.Load += new System.EventHandler(this.MachineTypeWindow_Load);
            ((System.ComponentModel.ISupportInitialize)(this.DataGrid)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.p0)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.p1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.p2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.p5)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.p4)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.p3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.machineTypeInfoBindingSource)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

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
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox TypeNo;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox TypeName;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.NumericUpDown p0;
        private System.Windows.Forms.NumericUpDown p1;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.NumericUpDown p2;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.NumericUpDown p5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.NumericUpDown p4;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.NumericUpDown p3;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
    }
}