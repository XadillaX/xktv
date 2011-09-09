namespace 前台系统.Windows
{
    partial class RegForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(RegForm));
            this.label1 = new System.Windows.Forms.Label();
            this.VIPNo = new System.Windows.Forms.TextBox();
            this.VIPName = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.VIPID = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.VIPMobile = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.Balance = new System.Windows.Forms.NumericUpDown();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.Balance)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 13);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(59, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "会员卡号:";
            // 
            // VIPNo
            // 
            this.VIPNo.Location = new System.Drawing.Point(78, 10);
            this.VIPNo.Name = "VIPNo";
            this.VIPNo.Size = new System.Drawing.Size(178, 21);
            this.VIPNo.TabIndex = 1;
            // 
            // VIPName
            // 
            this.VIPName.Location = new System.Drawing.Point(78, 37);
            this.VIPName.Name = "VIPName";
            this.VIPName.Size = new System.Drawing.Size(178, 21);
            this.VIPName.TabIndex = 3;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(13, 40);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(59, 12);
            this.label2.TabIndex = 2;
            this.label2.Text = "姓    名:";
            // 
            // VIPID
            // 
            this.VIPID.Location = new System.Drawing.Point(78, 64);
            this.VIPID.Name = "VIPID";
            this.VIPID.Size = new System.Drawing.Size(178, 21);
            this.VIPID.TabIndex = 5;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(13, 67);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(59, 12);
            this.label3.TabIndex = 4;
            this.label3.Text = "身 份 证:";
            // 
            // VIPMobile
            // 
            this.VIPMobile.Location = new System.Drawing.Point(78, 91);
            this.VIPMobile.Name = "VIPMobile";
            this.VIPMobile.Size = new System.Drawing.Size(178, 21);
            this.VIPMobile.TabIndex = 7;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(13, 94);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(59, 12);
            this.label4.TabIndex = 6;
            this.label4.Text = "手机号码:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(13, 121);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(59, 12);
            this.label5.TabIndex = 8;
            this.label5.Text = "初始资金:";
            // 
            // Balance
            // 
            this.Balance.DecimalPlaces = 2;
            this.Balance.Location = new System.Drawing.Point(78, 118);
            this.Balance.Maximum = new decimal(new int[] {
            1000000000,
            0,
            0,
            0});
            this.Balance.Name = "Balance";
            this.Balance.Size = new System.Drawing.Size(178, 21);
            this.Balance.TabIndex = 9;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(15, 154);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 10;
            this.button1.Text = "注册(&R)";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(181, 154);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 11;
            this.button2.Text = "关闭(&C)";
            this.button2.UseVisualStyleBackColor = true;
            // 
            // RegForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(268, 189);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.Balance);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.VIPMobile);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.VIPID);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.VIPName);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.VIPNo);
            this.Controls.Add(this.label1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "RegForm";
            this.Text = "新VIP会员";
            ((System.ComponentModel.ISupportInitialize)(this.Balance)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox VIPNo;
        private System.Windows.Forms.TextBox VIPName;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox VIPID;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox VIPMobile;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.NumericUpDown Balance;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
    }
}