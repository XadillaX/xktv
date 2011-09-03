namespace 前台系统
{
    partial class OrderMachineForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(OrderMachineForm));
            this.MachineNameLabel = new System.Windows.Forms.Label();
            this.TypeNameLabel = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.EVIPNo = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.ChooseDate = new System.Windows.Forms.DateTimePicker();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.HourBox = new System.Windows.Forms.NumericUpDown();
            this.MinuteBox = new System.Windows.Forms.NumericUpDown();
            this.LastLong = new System.Windows.Forms.NumericUpDown();
            this.LabelHour = new System.Windows.Forms.Label();
            this.EditVIP = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label7 = new System.Windows.Forms.Label();
            this.LBalance = new System.Windows.Forms.Label();
            this.LTotExp = new System.Windows.Forms.Label();
            this.LCurExp = new System.Windows.Forms.Label();
            this.LVIPID = new System.Windows.Forms.Label();
            this.LVIPName = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.LBudget = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.UseExp = new System.Windows.Forms.NumericUpDown();
            this.label9 = new System.Windows.Forms.Label();
            this.UseBalance = new System.Windows.Forms.NumericUpDown();
            this.label10 = new System.Windows.Forms.Label();
            this.Income = new System.Windows.Forms.NumericUpDown();
            this.OK = new System.Windows.Forms.Button();
            this.Cancel = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.HourBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.MinuteBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.LastLong)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.UseExp)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.UseBalance)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Income)).BeginInit();
            this.SuspendLayout();
            // 
            // MachineNameLabel
            // 
            this.MachineNameLabel.AutoSize = true;
            this.MachineNameLabel.Font = new System.Drawing.Font("微软雅黑", 24F);
            this.MachineNameLabel.Location = new System.Drawing.Point(-2, 2);
            this.MachineNameLabel.Name = "MachineNameLabel";
            this.MachineNameLabel.Size = new System.Drawing.Size(138, 41);
            this.MachineNameLabel.TabIndex = 0;
            this.MachineNameLabel.Text = "读取中...";
            // 
            // TypeNameLabel
            // 
            this.TypeNameLabel.AutoSize = true;
            this.TypeNameLabel.Location = new System.Drawing.Point(5, 47);
            this.TypeNameLabel.Name = "TypeNameLabel";
            this.TypeNameLabel.Size = new System.Drawing.Size(59, 12);
            this.TypeNameLabel.TabIndex = 1;
            this.TypeNameLabel.Text = "读取中...";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.Color.Transparent;
            this.label1.Location = new System.Drawing.Point(3, 52);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(317, 12);
            this.label1.TabIndex = 2;
            this.label1.Text = "____________________________________________________";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(9, 78);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(59, 12);
            this.label2.TabIndex = 3;
            this.label2.Text = "会员卡号:";
            // 
            // EVIPNo
            // 
            this.EVIPNo.Location = new System.Drawing.Point(74, 75);
            this.EVIPNo.Name = "EVIPNo";
            this.EVIPNo.Size = new System.Drawing.Size(140, 21);
            this.EVIPNo.TabIndex = 4;
            this.EVIPNo.Text = "0000000000";
            this.EVIPNo.KeyDown += new System.Windows.Forms.KeyEventHandler(this.EVIPNo_KeyDown);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(9, 117);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(59, 12);
            this.label3.TabIndex = 5;
            this.label3.Text = "开机时间:";
            // 
            // ChooseDate
            // 
            this.ChooseDate.Location = new System.Drawing.Point(74, 111);
            this.ChooseDate.Name = "ChooseDate";
            this.ChooseDate.Size = new System.Drawing.Size(140, 21);
            this.ChooseDate.TabIndex = 6;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(261, 117);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(11, 12);
            this.label4.TabIndex = 8;
            this.label4.Text = ":";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(9, 154);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(35, 12);
            this.label5.TabIndex = 10;
            this.label5.Text = "时长:";
            // 
            // HourBox
            // 
            this.HourBox.Location = new System.Drawing.Point(220, 111);
            this.HourBox.Maximum = new decimal(new int[] {
            23,
            0,
            0,
            0});
            this.HourBox.Name = "HourBox";
            this.HourBox.Size = new System.Drawing.Size(35, 21);
            this.HourBox.TabIndex = 11;
            this.HourBox.ValueChanged += new System.EventHandler(this.HourBox_ValueChanged);
            // 
            // MinuteBox
            // 
            this.MinuteBox.Location = new System.Drawing.Point(278, 111);
            this.MinuteBox.Maximum = new decimal(new int[] {
            59,
            0,
            0,
            0});
            this.MinuteBox.Name = "MinuteBox";
            this.MinuteBox.Size = new System.Drawing.Size(35, 21);
            this.MinuteBox.TabIndex = 12;
            // 
            // LastLong
            // 
            this.LastLong.Location = new System.Drawing.Point(74, 150);
            this.LastLong.Maximum = new decimal(new int[] {
            72,
            0,
            0,
            0});
            this.LastLong.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.LastLong.Name = "LastLong";
            this.LastLong.Size = new System.Drawing.Size(140, 21);
            this.LastLong.TabIndex = 13;
            this.LastLong.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.LastLong.ValueChanged += new System.EventHandler(this.LastLong_ValueChanged);
            // 
            // LabelHour
            // 
            this.LabelHour.AutoSize = true;
            this.LabelHour.Location = new System.Drawing.Point(220, 154);
            this.LabelHour.Name = "LabelHour";
            this.LabelHour.Size = new System.Drawing.Size(29, 12);
            this.LabelHour.TabIndex = 14;
            this.LabelHour.Text = "小时";
            // 
            // EditVIP
            // 
            this.EditVIP.Location = new System.Drawing.Point(220, 73);
            this.EditVIP.Name = "EditVIP";
            this.EditVIP.Size = new System.Drawing.Size(93, 23);
            this.EditVIP.TabIndex = 16;
            this.EditVIP.Text = "修改(&E)";
            this.EditVIP.UseVisualStyleBackColor = true;
            this.EditVIP.Click += new System.EventHandler(this.EditVIP_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.UseBalance);
            this.groupBox1.Controls.Add(this.label9);
            this.groupBox1.Controls.Add(this.UseExp);
            this.groupBox1.Controls.Add(this.label8);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.label7);
            this.groupBox1.Controls.Add(this.LBalance);
            this.groupBox1.Controls.Add(this.LTotExp);
            this.groupBox1.Controls.Add(this.LCurExp);
            this.groupBox1.Controls.Add(this.LVIPID);
            this.groupBox1.Controls.Add(this.LVIPName);
            this.groupBox1.Location = new System.Drawing.Point(9, 190);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(304, 207);
            this.groupBox1.TabIndex = 17;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "VIP信息";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(6, 127);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(59, 12);
            this.label7.TabIndex = 27;
            this.label7.Text = "使用余额:";
            // 
            // LBalance
            // 
            this.LBalance.AutoSize = true;
            this.LBalance.Location = new System.Drawing.Point(6, 96);
            this.LBalance.Name = "LBalance";
            this.LBalance.Size = new System.Drawing.Size(71, 12);
            this.LBalance.TabIndex = 26;
            this.LBalance.Text = "卡内余额: 0";
            // 
            // LTotExp
            // 
            this.LTotExp.AutoSize = true;
            this.LTotExp.Location = new System.Drawing.Point(6, 77);
            this.LTotExp.Name = "LTotExp";
            this.LTotExp.Size = new System.Drawing.Size(83, 12);
            this.LTotExp.TabIndex = 25;
            this.LTotExp.Text = "已使用积分: 0";
            // 
            // LCurExp
            // 
            this.LCurExp.AutoSize = true;
            this.LCurExp.Location = new System.Drawing.Point(6, 58);
            this.LCurExp.Name = "LCurExp";
            this.LCurExp.Size = new System.Drawing.Size(71, 12);
            this.LCurExp.TabIndex = 24;
            this.LCurExp.Text = "剩余积分: 0";
            // 
            // LVIPID
            // 
            this.LVIPID.AutoSize = true;
            this.LVIPID.Location = new System.Drawing.Point(6, 39);
            this.LVIPID.Name = "LVIPID";
            this.LVIPID.Size = new System.Drawing.Size(185, 12);
            this.LVIPID.TabIndex = 23;
            this.LVIPID.Text = "身份证号码: 000000000000000000";
            // 
            // LVIPName
            // 
            this.LVIPName.AutoSize = true;
            this.LVIPName.Location = new System.Drawing.Point(6, 20);
            this.LVIPName.Name = "LVIPName";
            this.LVIPName.Size = new System.Drawing.Size(113, 12);
            this.LVIPName.TabIndex = 22;
            this.LVIPName.Text = "会员姓名: 统一户头";
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.Cancel);
            this.panel1.Controls.Add(this.OK);
            this.panel1.Controls.Add(this.Income);
            this.panel1.Controls.Add(this.label10);
            this.panel1.Controls.Add(this.LBudget);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panel1.Location = new System.Drawing.Point(0, 417);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(324, 60);
            this.panel1.TabIndex = 18;
            // 
            // LBudget
            // 
            this.LBudget.AutoSize = true;
            this.LBudget.Location = new System.Drawing.Point(7, 11);
            this.LBudget.Name = "LBudget";
            this.LBudget.Size = new System.Drawing.Size(35, 12);
            this.LBudget.TabIndex = 16;
            this.LBudget.Text = "预算:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(211, 127);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(17, 12);
            this.label6.TabIndex = 29;
            this.label6.Text = "元";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(6, 162);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(59, 12);
            this.label8.TabIndex = 30;
            this.label8.Text = "积分换时:";
            // 
            // UseExp
            // 
            this.UseExp.Location = new System.Drawing.Point(66, 159);
            this.UseExp.Name = "UseExp";
            this.UseExp.Size = new System.Drawing.Size(139, 21);
            this.UseExp.TabIndex = 31;
            this.UseExp.ValueChanged += new System.EventHandler(this.UseExp_ValueChanged);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(211, 163);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(29, 12);
            this.label9.TabIndex = 32;
            this.label9.Text = "小时";
            // 
            // UseBalance
            // 
            this.UseBalance.DecimalPlaces = 2;
            this.UseBalance.Location = new System.Drawing.Point(65, 125);
            this.UseBalance.Name = "UseBalance";
            this.UseBalance.Size = new System.Drawing.Size(140, 21);
            this.UseBalance.TabIndex = 33;
            this.UseBalance.ValueChanged += new System.EventHandler(this.UseBalance_ValueChanged);
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(7, 36);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(35, 12);
            this.label10.TabIndex = 17;
            this.label10.Text = "实收:";
            // 
            // Income
            // 
            this.Income.DecimalPlaces = 2;
            this.Income.Location = new System.Drawing.Point(48, 31);
            this.Income.Maximum = new decimal(new int[] {
            1000000000,
            0,
            0,
            0});
            this.Income.Name = "Income";
            this.Income.Size = new System.Drawing.Size(120, 21);
            this.Income.TabIndex = 18;
            // 
            // OK
            // 
            this.OK.Location = new System.Drawing.Point(199, 11);
            this.OK.Name = "OK";
            this.OK.Size = new System.Drawing.Size(55, 41);
            this.OK.TabIndex = 19;
            this.OK.Text = "确定(&O)";
            this.OK.UseVisualStyleBackColor = true;
            this.OK.Click += new System.EventHandler(this.OK_Click);
            // 
            // Cancel
            // 
            this.Cancel.Location = new System.Drawing.Point(257, 11);
            this.Cancel.Name = "Cancel";
            this.Cancel.Size = new System.Drawing.Size(55, 41);
            this.Cancel.TabIndex = 20;
            this.Cancel.Text = "取消(&C)";
            this.Cancel.UseVisualStyleBackColor = true;
            this.Cancel.Click += new System.EventHandler(this.Cancel_Click);
            // 
            // OrderMachineForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(324, 477);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.EditVIP);
            this.Controls.Add(this.LabelHour);
            this.Controls.Add(this.LastLong);
            this.Controls.Add(this.MinuteBox);
            this.Controls.Add(this.HourBox);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.ChooseDate);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.EVIPNo);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.TypeNameLabel);
            this.Controls.Add(this.MachineNameLabel);
            this.Controls.Add(this.label1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "OrderMachineForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Load += new System.EventHandler(this.OrderMachineForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.HourBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.MinuteBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.LastLong)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.UseExp)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.UseBalance)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Income)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label MachineNameLabel;
        private System.Windows.Forms.Label TypeNameLabel;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox EVIPNo;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.DateTimePicker ChooseDate;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.NumericUpDown HourBox;
        private System.Windows.Forms.NumericUpDown MinuteBox;
        private System.Windows.Forms.NumericUpDown LastLong;
        private System.Windows.Forms.Label LabelHour;
        private System.Windows.Forms.Button EditVIP;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label LBalance;
        private System.Windows.Forms.Label LTotExp;
        private System.Windows.Forms.Label LCurExp;
        private System.Windows.Forms.Label LVIPID;
        private System.Windows.Forms.Label LVIPName;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label LBudget;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.NumericUpDown UseExp;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.NumericUpDown UseBalance;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.NumericUpDown Income;
        private System.Windows.Forms.Button Cancel;
        private System.Windows.Forms.Button OK;
    }
}