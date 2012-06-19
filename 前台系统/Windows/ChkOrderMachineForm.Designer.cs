namespace 前台系统
{
    partial class ChkOrderMachineForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ChkOrderMachineForm));
            this.LMachineNo = new System.Windows.Forms.Label();
            this.LMachineType = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.LVIPNo = new System.Windows.Forms.Label();
            this.LStartTime = new System.Windows.Forms.Label();
            this.LShutTime = new System.Windows.Forms.Label();
            this.LUseExp = new System.Windows.Forms.Label();
            this.LUseBalance = new System.Windows.Forms.Label();
            this.LMoney = new System.Windows.Forms.Label();
            this.LMoneyFact = new System.Windows.Forms.Label();
            this.LMoneyGiveBack = new System.Windows.Forms.Label();
            this.LUsername = new System.Windows.Forms.Label();
            this.LTime = new System.Windows.Forms.Label();
            this.OK = new System.Windows.Forms.Button();
            this.Cancel = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // LMachineNo
            // 
            this.LMachineNo.AutoSize = true;
            this.LMachineNo.Location = new System.Drawing.Point(12, 48);
            this.LMachineNo.Name = "LMachineNo";
            this.LMachineNo.Size = new System.Drawing.Size(95, 12);
            this.LMachineNo.TabIndex = 0;
            this.LMachineNo.Text = "包 厢 号: 00000";
            // 
            // LMachineType
            // 
            this.LMachineType.AutoSize = true;
            this.LMachineType.Location = new System.Drawing.Point(12, 72);
            this.LMachineType.Name = "LMachineType";
            this.LMachineType.Size = new System.Drawing.Size(95, 12);
            this.LMachineType.TabIndex = 1;
            this.LMachineType.Text = "包厢类型: 00000";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("微软雅黑", 15F);
            this.label3.Location = new System.Drawing.Point(83, 9);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(149, 27);
            this.label3.TabIndex = 2;
            this.label3.Text = "XKTV系统 订单";
            // 
            // LVIPNo
            // 
            this.LVIPNo.AutoSize = true;
            this.LVIPNo.Location = new System.Drawing.Point(12, 96);
            this.LVIPNo.Name = "LVIPNo";
            this.LVIPNo.Size = new System.Drawing.Size(125, 12);
            this.LVIPNo.TabIndex = 3;
            this.LVIPNo.Text = "会员账号: 0000000000";
            // 
            // LStartTime
            // 
            this.LStartTime.AutoSize = true;
            this.LStartTime.Location = new System.Drawing.Point(12, 120);
            this.LStartTime.Name = "LStartTime";
            this.LStartTime.Size = new System.Drawing.Size(161, 12);
            this.LStartTime.TabIndex = 4;
            this.LStartTime.Text = "开机时间: 1900/01/01 00:00";
            // 
            // LShutTime
            // 
            this.LShutTime.AutoSize = true;
            this.LShutTime.Location = new System.Drawing.Point(12, 144);
            this.LShutTime.Name = "LShutTime";
            this.LShutTime.Size = new System.Drawing.Size(161, 12);
            this.LShutTime.TabIndex = 5;
            this.LShutTime.Text = "关机时间: 1900/01/01 00:00";
            // 
            // LUseExp
            // 
            this.LUseExp.AutoSize = true;
            this.LUseExp.Location = new System.Drawing.Point(12, 168);
            this.LUseExp.Name = "LUseExp";
            this.LUseExp.Size = new System.Drawing.Size(101, 12);
            this.LUseExp.TabIndex = 6;
            this.LUseExp.Text = "使用积分: 0 小时";
            // 
            // LUseBalance
            // 
            this.LUseBalance.AutoSize = true;
            this.LUseBalance.Location = new System.Drawing.Point(12, 192);
            this.LUseBalance.Name = "LUseBalance";
            this.LUseBalance.Size = new System.Drawing.Size(107, 12);
            this.LUseBalance.TabIndex = 7;
            this.LUseBalance.Text = "使用余额: 0.00 元";
            // 
            // LMoney
            // 
            this.LMoney.AutoSize = true;
            this.LMoney.Location = new System.Drawing.Point(12, 230);
            this.LMoney.Name = "LMoney";
            this.LMoney.Size = new System.Drawing.Size(119, 12);
            this.LMoney.TabIndex = 8;
            this.LMoney.Text = "应收金额: 100.00 元";
            // 
            // LMoneyFact
            // 
            this.LMoneyFact.AutoSize = true;
            this.LMoneyFact.Location = new System.Drawing.Point(12, 251);
            this.LMoneyFact.Name = "LMoneyFact";
            this.LMoneyFact.Size = new System.Drawing.Size(119, 12);
            this.LMoneyFact.TabIndex = 9;
            this.LMoneyFact.Text = "实收金额: 100.00 元";
            // 
            // LMoneyGiveBack
            // 
            this.LMoneyGiveBack.AutoSize = true;
            this.LMoneyGiveBack.Location = new System.Drawing.Point(12, 272);
            this.LMoneyGiveBack.Name = "LMoneyGiveBack";
            this.LMoneyGiveBack.Size = new System.Drawing.Size(107, 12);
            this.LMoneyGiveBack.TabIndex = 10;
            this.LMoneyGiveBack.Text = "找    零: 0.00 元";
            // 
            // LUsername
            // 
            this.LUsername.AutoSize = true;
            this.LUsername.Location = new System.Drawing.Point(12, 304);
            this.LUsername.Name = "LUsername";
            this.LUsername.Size = new System.Drawing.Size(95, 12);
            this.LUsername.TabIndex = 11;
            this.LUsername.Text = "操 作 员: admin";
            // 
            // LTime
            // 
            this.LTime.AutoSize = true;
            this.LTime.Location = new System.Drawing.Point(11, 320);
            this.LTime.Name = "LTime";
            this.LTime.Size = new System.Drawing.Size(161, 12);
            this.LTime.TabIndex = 12;
            this.LTime.Text = "操作时间: 1900/01/01 00:00";
            // 
            // OK
            // 
            this.OK.Location = new System.Drawing.Point(76, 352);
            this.OK.Name = "OK";
            this.OK.Size = new System.Drawing.Size(75, 23);
            this.OK.TabIndex = 13;
            this.OK.Text = "确认(&O)";
            this.OK.UseVisualStyleBackColor = true;
            this.OK.Click += new System.EventHandler(this.Print_Click);
            // 
            // Cancel
            // 
            this.Cancel.Location = new System.Drawing.Point(157, 352);
            this.Cancel.Name = "Cancel";
            this.Cancel.Size = new System.Drawing.Size(75, 23);
            this.Cancel.TabIndex = 14;
            this.Cancel.Text = "取消(&C)";
            this.Cancel.UseVisualStyleBackColor = true;
            this.Cancel.Click += new System.EventHandler(this.Cancel_Click);
            // 
            // ChkOrderMachineForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(321, 387);
            this.Controls.Add(this.Cancel);
            this.Controls.Add(this.OK);
            this.Controls.Add(this.LTime);
            this.Controls.Add(this.LUsername);
            this.Controls.Add(this.LMoneyGiveBack);
            this.Controls.Add(this.LMoneyFact);
            this.Controls.Add(this.LMoney);
            this.Controls.Add(this.LUseBalance);
            this.Controls.Add(this.LUseExp);
            this.Controls.Add(this.LShutTime);
            this.Controls.Add(this.LStartTime);
            this.Controls.Add(this.LVIPNo);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.LMachineType);
            this.Controls.Add(this.LMachineNo);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "ChkOrderMachineForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "确认订单";
            this.Load += new System.EventHandler(this.ChkOrderMachineForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label LMachineNo;
        private System.Windows.Forms.Label LMachineType;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label LVIPNo;
        private System.Windows.Forms.Label LStartTime;
        private System.Windows.Forms.Label LShutTime;
        private System.Windows.Forms.Label LUseExp;
        private System.Windows.Forms.Label LUseBalance;
        private System.Windows.Forms.Label LMoney;
        private System.Windows.Forms.Label LMoneyFact;
        private System.Windows.Forms.Label LMoneyGiveBack;
        private System.Windows.Forms.Label LUsername;
        private System.Windows.Forms.Label LTime;
        private System.Windows.Forms.Button OK;
        private System.Windows.Forms.Button Cancel;
    }
}