namespace 前台系统
{
    partial class ContinueMachineForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ContinueMachineForm));
            this.TypeNameLabel = new System.Windows.Forms.Label();
            this.MachineNameLabel = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.LVIPNo = new System.Windows.Forms.Label();
            this.LStartTime = new System.Windows.Forms.Label();
            this.LShutTime = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.BoxLastLong = new System.Windows.Forms.NumericUpDown();
            this.label6 = new System.Windows.Forms.Label();
            this.IsNight = new System.Windows.Forms.CheckBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.label12 = new System.Windows.Forms.Label();
            this.BoxMoney = new System.Windows.Forms.NumericUpDown();
            this.label11 = new System.Windows.Forms.Label();
            this.LMoney = new System.Windows.Forms.Label();
            this.LBalance = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.BoxUseBalance = new System.Windows.Forms.NumericUpDown();
            this.label9 = new System.Windows.Forms.Label();
            this.Cancel = new System.Windows.Forms.Button();
            this.OK = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.BoxLastLong)).BeginInit();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.BoxMoney)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.BoxUseBalance)).BeginInit();
            this.SuspendLayout();
            // 
            // TypeNameLabel
            // 
            this.TypeNameLabel.AutoSize = true;
            this.TypeNameLabel.Location = new System.Drawing.Point(10, 54);
            this.TypeNameLabel.Name = "TypeNameLabel";
            this.TypeNameLabel.Size = new System.Drawing.Size(59, 12);
            this.TypeNameLabel.TabIndex = 4;
            this.TypeNameLabel.Text = "读取中...";
            // 
            // MachineNameLabel
            // 
            this.MachineNameLabel.AutoSize = true;
            this.MachineNameLabel.Font = new System.Drawing.Font("微软雅黑", 24F);
            this.MachineNameLabel.Location = new System.Drawing.Point(3, 9);
            this.MachineNameLabel.Name = "MachineNameLabel";
            this.MachineNameLabel.Size = new System.Drawing.Size(138, 41);
            this.MachineNameLabel.TabIndex = 3;
            this.MachineNameLabel.Text = "读取中...";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.Color.Transparent;
            this.label1.Location = new System.Drawing.Point(8, 59);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(317, 12);
            this.label1.TabIndex = 5;
            this.label1.Text = "____________________________________________________";
            // 
            // LVIPNo
            // 
            this.LVIPNo.AutoSize = true;
            this.LVIPNo.Location = new System.Drawing.Point(10, 79);
            this.LVIPNo.Name = "LVIPNo";
            this.LVIPNo.Size = new System.Drawing.Size(125, 12);
            this.LVIPNo.TabIndex = 6;
            this.LVIPNo.Text = "会员账号: 0000000000";
            // 
            // LStartTime
            // 
            this.LStartTime.AutoSize = true;
            this.LStartTime.Location = new System.Drawing.Point(10, 95);
            this.LStartTime.Name = "LStartTime";
            this.LStartTime.Size = new System.Drawing.Size(161, 12);
            this.LStartTime.TabIndex = 7;
            this.LStartTime.Text = "开机时间: 1900/01/01 00:00";
            // 
            // LShutTime
            // 
            this.LShutTime.AutoSize = true;
            this.LShutTime.Location = new System.Drawing.Point(10, 112);
            this.LShutTime.Name = "LShutTime";
            this.LShutTime.Size = new System.Drawing.Size(161, 12);
            this.LShutTime.TabIndex = 8;
            this.LShutTime.Text = "关机时间: 1900/01/01 00:00";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(10, 148);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(59, 12);
            this.label5.TabIndex = 9;
            this.label5.Text = "续费时长:";
            // 
            // BoxLastLong
            // 
            this.BoxLastLong.Location = new System.Drawing.Point(72, 143);
            this.BoxLastLong.Maximum = new decimal(new int[] {
            24,
            0,
            0,
            0});
            this.BoxLastLong.Name = "BoxLastLong";
            this.BoxLastLong.Size = new System.Drawing.Size(63, 21);
            this.BoxLastLong.TabIndex = 10;
            this.BoxLastLong.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.BoxLastLong.ValueChanged += new System.EventHandler(this.BoxLastLong_ValueChanged);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(141, 148);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(29, 12);
            this.label6.TabIndex = 11;
            this.label6.Text = "小时";
            // 
            // IsNight
            // 
            this.IsNight.AutoSize = true;
            this.IsNight.Location = new System.Drawing.Point(72, 170);
            this.IsNight.Name = "IsNight";
            this.IsNight.Size = new System.Drawing.Size(72, 16);
            this.IsNight.TabIndex = 13;
            this.IsNight.Text = "是否包夜";
            this.IsNight.UseVisualStyleBackColor = true;
            this.IsNight.CheckedChanged += new System.EventHandler(this.IsNight_CheckedChanged);
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.label12);
            this.panel1.Controls.Add(this.BoxMoney);
            this.panel1.Controls.Add(this.label11);
            this.panel1.Controls.Add(this.LMoney);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panel1.Location = new System.Drawing.Point(0, 272);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(333, 57);
            this.panel1.TabIndex = 14;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(141, 35);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(17, 12);
            this.label12.TabIndex = 22;
            this.label12.Text = "元";
            // 
            // BoxMoney
            // 
            this.BoxMoney.DecimalPlaces = 2;
            this.BoxMoney.Location = new System.Drawing.Point(72, 32);
            this.BoxMoney.Maximum = new decimal(new int[] {
            1000000000,
            0,
            0,
            0});
            this.BoxMoney.Name = "BoxMoney";
            this.BoxMoney.Size = new System.Drawing.Size(63, 21);
            this.BoxMoney.TabIndex = 21;
            this.BoxMoney.ValueChanged += new System.EventHandler(this.BoxMoney_ValueChanged);
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(10, 36);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(65, 12);
            this.label11.TabIndex = 1;
            this.label11.Text = "实际付款: ";
            // 
            // LMoney
            // 
            this.LMoney.AutoSize = true;
            this.LMoney.Location = new System.Drawing.Point(10, 14);
            this.LMoney.Name = "LMoney";
            this.LMoney.Size = new System.Drawing.Size(101, 12);
            this.LMoney.TabIndex = 0;
            this.LMoney.Text = "预计付款: 0.00元";
            // 
            // LBalance
            // 
            this.LBalance.AutoSize = true;
            this.LBalance.Location = new System.Drawing.Point(10, 208);
            this.LBalance.Name = "LBalance";
            this.LBalance.Size = new System.Drawing.Size(107, 12);
            this.LBalance.TabIndex = 15;
            this.LBalance.Text = "会员余额: 0.00 元";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(10, 234);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(59, 12);
            this.label8.TabIndex = 16;
            this.label8.Text = "使用余额:";
            // 
            // BoxUseBalance
            // 
            this.BoxUseBalance.DecimalPlaces = 2;
            this.BoxUseBalance.Location = new System.Drawing.Point(72, 231);
            this.BoxUseBalance.Name = "BoxUseBalance";
            this.BoxUseBalance.Size = new System.Drawing.Size(63, 21);
            this.BoxUseBalance.TabIndex = 17;
            this.BoxUseBalance.ValueChanged += new System.EventHandler(this.BoxUseBalance_ValueChanged);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(141, 234);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(17, 12);
            this.label9.TabIndex = 18;
            this.label9.Text = "元";
            // 
            // Cancel
            // 
            this.Cancel.Location = new System.Drawing.Point(266, 134);
            this.Cancel.Name = "Cancel";
            this.Cancel.Size = new System.Drawing.Size(55, 41);
            this.Cancel.TabIndex = 26;
            this.Cancel.Text = "取消(&C)";
            this.Cancel.UseVisualStyleBackColor = true;
            this.Cancel.Click += new System.EventHandler(this.Cancel_Click);
            // 
            // OK
            // 
            this.OK.Location = new System.Drawing.Point(266, 79);
            this.OK.Name = "OK";
            this.OK.Size = new System.Drawing.Size(55, 41);
            this.OK.TabIndex = 25;
            this.OK.Text = "确定(&O)";
            this.OK.UseVisualStyleBackColor = true;
            this.OK.Click += new System.EventHandler(this.OK_Click);
            // 
            // ContinueMachineForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(333, 329);
            this.Controls.Add(this.Cancel);
            this.Controls.Add(this.OK);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.BoxUseBalance);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.LBalance);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.IsNight);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.BoxLastLong);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.LShutTime);
            this.Controls.Add(this.LStartTime);
            this.Controls.Add(this.LVIPNo);
            this.Controls.Add(this.TypeNameLabel);
            this.Controls.Add(this.MachineNameLabel);
            this.Controls.Add(this.label1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "ContinueMachineForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "包厢续费";
            this.Load += new System.EventHandler(this.ContinueMachineForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.BoxLastLong)).EndInit();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.BoxMoney)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.BoxUseBalance)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label TypeNameLabel;
        private System.Windows.Forms.Label MachineNameLabel;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label LVIPNo;
        private System.Windows.Forms.Label LStartTime;
        private System.Windows.Forms.Label LShutTime;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.NumericUpDown BoxLastLong;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.CheckBox IsNight;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label LBalance;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.NumericUpDown BoxUseBalance;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label LMoney;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.NumericUpDown BoxMoney;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Button Cancel;
        private System.Windows.Forms.Button OK;
    }
}