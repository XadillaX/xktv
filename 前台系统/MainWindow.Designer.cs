namespace 前台系统
{
    partial class MainWindow
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainWindow));
            this.Panel = new System.Windows.Forms.Panel();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.系统SToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.退出QToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.包厢MToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.空闲包厢FToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.ShowUsername = new System.Windows.Forms.ToolStripStatusLabel();
            this.Panel.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // Panel
            // 
            this.Panel.AutoScroll = true;
            this.Panel.Controls.Add(this.statusStrip1);
            this.Panel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.Panel.Location = new System.Drawing.Point(0, 24);
            this.Panel.Margin = new System.Windows.Forms.Padding(0);
            this.Panel.Name = "Panel";
            this.Panel.Size = new System.Drawing.Size(619, 403);
            this.Panel.TabIndex = 0;
            this.Panel.Tag = "";
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.系统SToolStripMenuItem,
            this.包厢MToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(619, 24);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // 系统SToolStripMenuItem
            // 
            this.系统SToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.退出QToolStripMenuItem});
            this.系统SToolStripMenuItem.Name = "系统SToolStripMenuItem";
            this.系统SToolStripMenuItem.Size = new System.Drawing.Size(57, 20);
            this.系统SToolStripMenuItem.Text = "系统(&S)";
            // 
            // 退出QToolStripMenuItem
            // 
            this.退出QToolStripMenuItem.Name = "退出QToolStripMenuItem";
            this.退出QToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.退出QToolStripMenuItem.Text = "退出(&Q)";
            this.退出QToolStripMenuItem.Click += new System.EventHandler(this.退出QToolStripMenuItem_Click);
            // 
            // 包厢MToolStripMenuItem
            // 
            this.包厢MToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.空闲包厢FToolStripMenuItem});
            this.包厢MToolStripMenuItem.Name = "包厢MToolStripMenuItem";
            this.包厢MToolStripMenuItem.Size = new System.Drawing.Size(62, 20);
            this.包厢MToolStripMenuItem.Text = "包厢(&M)";
            // 
            // 空闲包厢FToolStripMenuItem
            // 
            this.空闲包厢FToolStripMenuItem.Name = "空闲包厢FToolStripMenuItem";
            this.空闲包厢FToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.F)));
            this.空闲包厢FToolStripMenuItem.Size = new System.Drawing.Size(176, 22);
            this.空闲包厢FToolStripMenuItem.Text = "空闲包厢(&F)";
            this.空闲包厢FToolStripMenuItem.Click += new System.EventHandler(this.空闲包厢FToolStripMenuItem_Click);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ShowUsername});
            this.statusStrip1.Location = new System.Drawing.Point(0, 381);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(619, 22);
            this.statusStrip1.TabIndex = 0;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // ShowUsername
            // 
            this.ShowUsername.Name = "ShowUsername";
            this.ShowUsername.Size = new System.Drawing.Size(46, 17);
            this.ShowUsername.Text = "用户名:";
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(619, 427);
            this.Controls.Add(this.Panel);
            this.Controls.Add(this.menuStrip1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MinimizeBox = false;
            this.Name = "MainWindow";
            this.Text = "KTV系统·前台";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.Load += new System.EventHandler(this.MainWindow_Load);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.MainWindow_FormClosed);
            this.Resize += new System.EventHandler(this.MainWindow_Resize);
            this.Panel.ResumeLayout(false);
            this.Panel.PerformLayout();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Panel Panel;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 系统SToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 退出QToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 包厢MToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 空闲包厢FToolStripMenuItem;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel ShowUsername;
    }
}