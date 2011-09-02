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
            this.VIPNo = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.ChooseDate = new System.Windows.Forms.DateTimePicker();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.HourBox = new System.Windows.Forms.NumericUpDown();
            this.MinuteBox = new System.Windows.Forms.NumericUpDown();
            this.LastLong = new System.Windows.Forms.NumericUpDown();
            this.LabelHour = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.EditVIP = new System.Windows.Forms.Button();
            this.label7 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.HourBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.MinuteBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.LastLong)).BeginInit();
            this.SuspendLayout();
            // 
            // MachineNameLabel
            // 
            this.MachineNameLabel.AutoSize = true;
            this.MachineNameLabel.Font = new System.Drawing.Font("微软雅黑", 24F);
            this.MachineNameLabel.Location = new System.Drawing.Point(2, 2);
            this.MachineNameLabel.Name = "MachineNameLabel";
            this.MachineNameLabel.Size = new System.Drawing.Size(138, 41);
            this.MachineNameLabel.TabIndex = 0;
            this.MachineNameLabel.Text = "读取中...";
            // 
            // TypeNameLabel
            // 
            this.TypeNameLabel.AutoSize = true;
            this.TypeNameLabel.Location = new System.Drawing.Point(9, 47);
            this.TypeNameLabel.Name = "TypeNameLabel";
            this.TypeNameLabel.Size = new System.Drawing.Size(59, 12);
            this.TypeNameLabel.TabIndex = 1;
            this.TypeNameLabel.Text = "读取中...";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.Color.Transparent;
            this.label1.Location = new System.Drawing.Point(9, 52);
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
            // VIPNo
            // 
            this.VIPNo.Location = new System.Drawing.Point(74, 75);
            this.VIPNo.Name = "VIPNo";
            this.VIPNo.Size = new System.Drawing.Size(140, 21);
            this.VIPNo.TabIndex = 4;
            this.VIPNo.Text = "0000000000";
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
            this.LastLong.Name = "LastLong";
            this.LastLong.Size = new System.Drawing.Size(140, 21);
            this.LastLong.TabIndex = 13;
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
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(9, 208);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(35, 12);
            this.label6.TabIndex = 15;
            this.label6.Text = "预算:";
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
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(8, 183);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(125, 12);
            this.label7.TabIndex = 17;
            this.label7.Text = "会员卡号: 0000000000";
            // 
            // OrderMachineForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(334, 235);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.EditVIP);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.LabelHour);
            this.Controls.Add(this.LastLong);
            this.Controls.Add(this.MinuteBox);
            this.Controls.Add(this.HourBox);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.ChooseDate);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.VIPNo);
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
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label MachineNameLabel;
        private System.Windows.Forms.Label TypeNameLabel;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox VIPNo;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.DateTimePicker ChooseDate;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.NumericUpDown HourBox;
        private System.Windows.Forms.NumericUpDown MinuteBox;
        private System.Windows.Forms.NumericUpDown LastLong;
        private System.Windows.Forms.Label LabelHour;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button EditVIP;
        private System.Windows.Forms.Label label7;
    }
}