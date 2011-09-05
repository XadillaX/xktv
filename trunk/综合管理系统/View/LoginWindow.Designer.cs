namespace KTV
{
    partial class LoginWindow
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(LoginWindow));
            this.LoginPanel = new System.Windows.Forms.Panel();
            this.CloseBtn = new QLFUI.Button();
            this.Password = new System.Windows.Forms.TextBox();
            this.Username = new System.Windows.Forms.TextBox();
            this.LoginBtn = new QLFUI.Button();
            this.Functions = new System.Windows.Forms.Panel();
            this.FuncClose = new QLFUI.Button();
            this.LoginPanel.SuspendLayout();
            this.Functions.SuspendLayout();
            this.SuspendLayout();
            // 
            // LoginPanel
            // 
            this.LoginPanel.BackColor = System.Drawing.Color.Transparent;
            this.LoginPanel.BackgroundImage = global::KTV.Properties.Resources.LoginBG;
            this.LoginPanel.Controls.Add(this.CloseBtn);
            this.LoginPanel.Controls.Add(this.Password);
            this.LoginPanel.Controls.Add(this.Username);
            this.LoginPanel.Controls.Add(this.LoginBtn);
            this.LoginPanel.Location = new System.Drawing.Point(252, 182);
            this.LoginPanel.Name = "LoginPanel";
            this.LoginPanel.Size = new System.Drawing.Size(296, 254);
            this.LoginPanel.TabIndex = 0;
            // 
            // CloseBtn
            // 
            this.CloseBtn.BackColor = System.Drawing.Color.Transparent;
            this.CloseBtn.BackgroundImage = global::KTV.Properties.Resources.blank;
            this.CloseBtn.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.CloseBtn.Caption = "";
            this.CloseBtn.DownImage = global::KTV.Properties.Resources.btn_close;
            this.CloseBtn.Location = new System.Drawing.Point(253, 29);
            this.CloseBtn.MoveImage = global::KTV.Properties.Resources.blank;
            this.CloseBtn.Name = "CloseBtn";
            this.CloseBtn.NormalImage = global::KTV.Properties.Resources.blank;
            this.CloseBtn.Size = new System.Drawing.Size(16, 23);
            this.CloseBtn.TabIndex = 13;
            this.CloseBtn.Load += new System.EventHandler(this.CloseBtn_Load);
            this.CloseBtn.Click += new System.EventHandler(this.CloseBtn_Click);
            // 
            // Password
            // 
            this.Password.BackColor = System.Drawing.Color.Black;
            this.Password.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.Password.ForeColor = System.Drawing.Color.White;
            this.Password.Location = new System.Drawing.Point(104, 119);
            this.Password.Name = "Password";
            this.Password.PasswordChar = '*';
            this.Password.Size = new System.Drawing.Size(123, 14);
            this.Password.TabIndex = 12;
            this.Password.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Username_KeyDown);
            // 
            // Username
            // 
            this.Username.BackColor = System.Drawing.Color.Black;
            this.Username.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.Username.ForeColor = System.Drawing.Color.White;
            this.Username.Location = new System.Drawing.Point(104, 88);
            this.Username.Name = "Username";
            this.Username.Size = new System.Drawing.Size(123, 14);
            this.Username.TabIndex = 11;
            this.Username.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Username_KeyDown);
            // 
            // LoginBtn
            // 
            this.LoginBtn.BackColor = System.Drawing.Color.Transparent;
            this.LoginBtn.BackgroundImage = global::KTV.Properties.Resources.blank;
            this.LoginBtn.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.LoginBtn.Caption = "";
            this.LoginBtn.DownImage = global::KTV.Properties.Resources.btn_login;
            this.LoginBtn.Location = new System.Drawing.Point(172, 165);
            this.LoginBtn.MoveImage = global::KTV.Properties.Resources.blank;
            this.LoginBtn.Name = "LoginBtn";
            this.LoginBtn.NormalImage = global::KTV.Properties.Resources.blank;
            this.LoginBtn.Size = new System.Drawing.Size(76, 33);
            this.LoginBtn.TabIndex = 10;
            this.LoginBtn.Click += new System.EventHandler(this.LoginBtn_Click);
            // 
            // Functions
            // 
            this.Functions.BackColor = System.Drawing.Color.Transparent;
            this.Functions.BackgroundImage = global::KTV.Properties.Resources.ListBox;
            this.Functions.Controls.Add(this.FuncClose);
            this.Functions.Location = new System.Drawing.Point(246, 75);
            this.Functions.Name = "Functions";
            this.Functions.Size = new System.Drawing.Size(308, 450);
            this.Functions.TabIndex = 1;
            this.Functions.Visible = false;
            // 
            // FuncClose
            // 
            this.FuncClose.BackColor = System.Drawing.Color.Transparent;
            this.FuncClose.BackgroundImage = global::KTV.Properties.Resources.blank;
            this.FuncClose.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.FuncClose.Caption = "";
            this.FuncClose.DownImage = global::KTV.Properties.Resources.btn_close;
            this.FuncClose.Location = new System.Drawing.Point(244, 30);
            this.FuncClose.MoveImage = global::KTV.Properties.Resources.blank;
            this.FuncClose.Name = "FuncClose";
            this.FuncClose.NormalImage = global::KTV.Properties.Resources.blank;
            this.FuncClose.Size = new System.Drawing.Size(16, 23);
            this.FuncClose.TabIndex = 14;
            this.FuncClose.Click += new System.EventHandler(this.CloseBtn_Click);
            // 
            // LoginWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Black;
            this.BackgroundImage = global::KTV.Properties.Resources.InitBackground;
            this.ClientSize = new System.Drawing.Size(800, 600);
            this.Controls.Add(this.Functions);
            this.Controls.Add(this.LoginPanel);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "LoginWindow";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "KTV点播系统·综合管理系统（声色版）";
            this.Load += new System.EventHandler(this.LoginWindow_Load);
            this.LoginPanel.ResumeLayout(false);
            this.LoginPanel.PerformLayout();
            this.Functions.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel LoginPanel;
        private QLFUI.Button LoginBtn;
        private System.Windows.Forms.TextBox Username;
        private System.Windows.Forms.TextBox Password;
        private QLFUI.Button CloseBtn;
        private System.Windows.Forms.Panel Functions;
        private QLFUI.Button FuncClose;
    }
}

