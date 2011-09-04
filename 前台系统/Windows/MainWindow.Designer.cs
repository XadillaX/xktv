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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.系统SToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.本人营业一览EToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.退出QToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.包厢MToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.空闲包厢FToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.包厢一览VToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.会员VToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.新VIP用户NToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.vIP用户充值充值ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.ShowUsername = new System.Windows.Forms.ToolStripStatusLabel();
            this.Panel = new System.Windows.Forms.Panel();
            this.MachineCount = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.menuStrip1.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.系统SToolStripMenuItem,
            this.包厢MToolStripMenuItem,
            this.会员VToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(619, 25);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // 系统SToolStripMenuItem
            // 
            this.系统SToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.本人营业一览EToolStripMenuItem,
            this.退出QToolStripMenuItem});
            this.系统SToolStripMenuItem.Name = "系统SToolStripMenuItem";
            this.系统SToolStripMenuItem.Size = new System.Drawing.Size(59, 21);
            this.系统SToolStripMenuItem.Text = "系统(&S)";
            // 
            // 本人营业一览EToolStripMenuItem
            // 
            this.本人营业一览EToolStripMenuItem.Name = "本人营业一览EToolStripMenuItem";
            this.本人营业一览EToolStripMenuItem.Size = new System.Drawing.Size(139, 22);
            this.本人营业一览EToolStripMenuItem.Text = "营业一览(&E)";
            // 
            // 退出QToolStripMenuItem
            // 
            this.退出QToolStripMenuItem.Name = "退出QToolStripMenuItem";
            this.退出QToolStripMenuItem.Size = new System.Drawing.Size(139, 22);
            this.退出QToolStripMenuItem.Text = "退出(&Q)";
            this.退出QToolStripMenuItem.Click += new System.EventHandler(this.退出QToolStripMenuItem_Click);
            // 
            // 包厢MToolStripMenuItem
            // 
            this.包厢MToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.空闲包厢FToolStripMenuItem,
            this.包厢一览VToolStripMenuItem});
            this.包厢MToolStripMenuItem.Name = "包厢MToolStripMenuItem";
            this.包厢MToolStripMenuItem.Size = new System.Drawing.Size(64, 21);
            this.包厢MToolStripMenuItem.Text = "包厢(&M)";
            // 
            // 空闲包厢FToolStripMenuItem
            // 
            this.空闲包厢FToolStripMenuItem.Name = "空闲包厢FToolStripMenuItem";
            this.空闲包厢FToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.F)));
            this.空闲包厢FToolStripMenuItem.Size = new System.Drawing.Size(189, 22);
            this.空闲包厢FToolStripMenuItem.Text = "空闲包厢(&F)";
            this.空闲包厢FToolStripMenuItem.Click += new System.EventHandler(this.空闲包厢FToolStripMenuItem_Click);
            // 
            // 包厢一览VToolStripMenuItem
            // 
            this.包厢一览VToolStripMenuItem.Name = "包厢一览VToolStripMenuItem";
            this.包厢一览VToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.W)));
            this.包厢一览VToolStripMenuItem.Size = new System.Drawing.Size(189, 22);
            this.包厢一览VToolStripMenuItem.Text = "包厢一览(&V)";
            this.包厢一览VToolStripMenuItem.Click += new System.EventHandler(this.包厢一览VToolStripMenuItem_Click);
            // 
            // 会员VToolStripMenuItem
            // 
            this.会员VToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.新VIP用户NToolStripMenuItem,
            this.vIP用户充值充值ToolStripMenuItem});
            this.会员VToolStripMenuItem.Name = "会员VToolStripMenuItem";
            this.会员VToolStripMenuItem.Size = new System.Drawing.Size(60, 21);
            this.会员VToolStripMenuItem.Text = "会员(&V)";
            // 
            // 新VIP用户NToolStripMenuItem
            // 
            this.新VIP用户NToolStripMenuItem.Name = "新VIP用户NToolStripMenuItem";
            this.新VIP用户NToolStripMenuItem.Size = new System.Drawing.Size(158, 22);
            this.新VIP用户NToolStripMenuItem.Text = "新VIP用户(&N)";
            // 
            // vIP用户充值充值ToolStripMenuItem
            // 
            this.vIP用户充值充值ToolStripMenuItem.Name = "vIP用户充值充值ToolStripMenuItem";
            this.vIP用户充值充值ToolStripMenuItem.Size = new System.Drawing.Size(158, 22);
            this.vIP用户充值充值ToolStripMenuItem.Text = "VIP用户充值(&P)";
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ShowUsername,
            this.toolStripStatusLabel1,
            this.MachineCount});
            this.statusStrip1.Location = new System.Drawing.Point(0, 467);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(619, 22);
            this.statusStrip1.TabIndex = 2;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // ShowUsername
            // 
            this.ShowUsername.Name = "ShowUsername";
            this.ShowUsername.Size = new System.Drawing.Size(47, 17);
            this.ShowUsername.Text = "用户名:";
            // 
            // Panel
            // 
            this.Panel.AutoScroll = true;
            this.Panel.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.Panel.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.Panel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.Panel.Location = new System.Drawing.Point(0, 25);
            this.Panel.Margin = new System.Windows.Forms.Padding(0);
            this.Panel.Name = "Panel";
            this.Panel.Size = new System.Drawing.Size(619, 442);
            this.Panel.TabIndex = 3;
            this.Panel.Tag = "";
            // 
            // MachineCount
            // 
            this.MachineCount.Name = "MachineCount";
            this.MachineCount.Size = new System.Drawing.Size(63, 17);
            this.MachineCount.Text = "包厢数量: ";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(11, 17);
            this.toolStripStatusLabel1.Text = "|";
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(619, 489);
            this.Controls.Add(this.Panel);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.menuStrip1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MinimizeBox = false;
            this.Name = "MainWindow";
            this.Text = "KTV系统·前台";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.Load += new System.EventHandler(this.MainWindow_Load);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.MainWindow_FormClosed);
            this.Resize += new System.EventHandler(this.MainWindow_Resize);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 系统SToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 退出QToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 包厢MToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 空闲包厢FToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 包厢一览VToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 会员VToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 新VIP用户NToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem vIP用户充值充值ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 本人营业一览EToolStripMenuItem;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel ShowUsername;
        private System.Windows.Forms.Panel Panel;
        private System.Windows.Forms.ToolStripStatusLabel MachineCount;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
    }
}