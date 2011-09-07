namespace KTV.View
{
    partial class ChangePwdWindow
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ChangePwdWindow));
            this.label1 = new System.Windows.Forms.Label();
            this.Username = new System.Windows.Forms.TextBox();
            this.Password = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.NewPassword = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.RePassword = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.Modify = new System.Windows.Forms.Button();
            this.Cancel = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(83, 65);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(47, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "用户名:";
            // 
            // Username
            // 
            this.Username.Location = new System.Drawing.Point(136, 62);
            this.Username.Name = "Username";
            this.Username.Size = new System.Drawing.Size(140, 21);
            this.Username.TabIndex = 1;
            this.Username.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Username_KeyDown);
            // 
            // Password
            // 
            this.Password.Location = new System.Drawing.Point(136, 89);
            this.Password.Name = "Password";
            this.Password.PasswordChar = '*';
            this.Password.Size = new System.Drawing.Size(140, 21);
            this.Password.TabIndex = 3;
            this.Password.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Username_KeyDown);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(83, 92);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(47, 12);
            this.label2.TabIndex = 2;
            this.label2.Text = "密  码:";
            // 
            // NewPassword
            // 
            this.NewPassword.Location = new System.Drawing.Point(136, 136);
            this.NewPassword.Name = "NewPassword";
            this.NewPassword.PasswordChar = '*';
            this.NewPassword.Size = new System.Drawing.Size(140, 21);
            this.NewPassword.TabIndex = 5;
            this.NewPassword.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Username_KeyDown);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(83, 139);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(47, 12);
            this.label3.TabIndex = 4;
            this.label3.Text = "新密码:";
            // 
            // RePassword
            // 
            this.RePassword.Location = new System.Drawing.Point(136, 163);
            this.RePassword.Name = "RePassword";
            this.RePassword.PasswordChar = '*';
            this.RePassword.Size = new System.Drawing.Size(140, 21);
            this.RePassword.TabIndex = 7;
            this.RePassword.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Username_KeyDown);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(83, 166);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(47, 12);
            this.label4.TabIndex = 6;
            this.label4.Text = "重  复:";
            // 
            // Modify
            // 
            this.Modify.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Modify.Location = new System.Drawing.Point(85, 210);
            this.Modify.Name = "Modify";
            this.Modify.Size = new System.Drawing.Size(75, 23);
            this.Modify.TabIndex = 8;
            this.Modify.Text = "修改(&M)";
            this.Modify.UseVisualStyleBackColor = true;
            this.Modify.Click += new System.EventHandler(this.Modify_Click);
            // 
            // Cancel
            // 
            this.Cancel.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Cancel.Location = new System.Drawing.Point(201, 210);
            this.Cancel.Name = "Cancel";
            this.Cancel.Size = new System.Drawing.Size(75, 23);
            this.Cancel.TabIndex = 9;
            this.Cancel.Text = "取消(&C)";
            this.Cancel.UseVisualStyleBackColor = true;
            this.Cancel.Click += new System.EventHandler(this.Cancel_Click);
            // 
            // ChangePwdWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.ClientSize = new System.Drawing.Size(367, 287);
            this.Controls.Add(this.Cancel);
            this.Controls.Add(this.Modify);
            this.Controls.Add(this.RePassword);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.NewPassword);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.Password);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.Username);
            this.Controls.Add(this.label1);
            this.ForeColor = System.Drawing.Color.White;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "ChangePwdWindow";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "修改密码";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox Username;
        private System.Windows.Forms.TextBox Password;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox NewPassword;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox RePassword;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button Modify;
        private System.Windows.Forms.Button Cancel;
    }
}