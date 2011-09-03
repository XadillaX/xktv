namespace 前台系统
{
    partial class MachineStateView
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
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MachineStateView));
            this.DataGrid = new System.Windows.Forms.DataGridView();
            this.MachineNo = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.TypeName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Status = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ShutTime = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.TimeLeft = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Refresh = new System.Windows.Forms.Button();
            this.Cancel = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.DataGrid)).BeginInit();
            this.SuspendLayout();
            // 
            // DataGrid
            // 
            this.DataGrid.AllowUserToAddRows = false;
            this.DataGrid.AllowUserToResizeRows = false;
            this.DataGrid.BackgroundColor = System.Drawing.SystemColors.ButtonHighlight;
            this.DataGrid.CellBorderStyle = System.Windows.Forms.DataGridViewCellBorderStyle.Raised;
            this.DataGrid.ColumnHeadersBorderStyle = System.Windows.Forms.DataGridViewHeaderBorderStyle.Single;
            this.DataGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.DataGrid.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.MachineNo,
            this.TypeName,
            this.Status,
            this.ShutTime,
            this.TimeLeft});
            this.DataGrid.Location = new System.Drawing.Point(12, 12);
            this.DataGrid.Name = "DataGrid";
            this.DataGrid.ReadOnly = true;
            this.DataGrid.RowHeadersBorderStyle = System.Windows.Forms.DataGridViewHeaderBorderStyle.None;
            this.DataGrid.RowHeadersVisible = false;
            this.DataGrid.RowTemplate.Height = 23;
            this.DataGrid.Size = new System.Drawing.Size(504, 397);
            this.DataGrid.TabIndex = 0;
            this.DataGrid.CellMouseDoubleClick += new System.Windows.Forms.DataGridViewCellMouseEventHandler(this.DataGrid_CellMouseDoubleClick);
            // 
            // MachineNo
            // 
            dataGridViewCellStyle1.ForeColor = System.Drawing.Color.Black;
            this.MachineNo.DefaultCellStyle = dataGridViewCellStyle1;
            this.MachineNo.HeaderText = "包厢名";
            this.MachineNo.Name = "MachineNo";
            this.MachineNo.ReadOnly = true;
            // 
            // TypeName
            // 
            this.TypeName.HeaderText = "包厢类型";
            this.TypeName.Name = "TypeName";
            this.TypeName.ReadOnly = true;
            // 
            // Status
            // 
            this.Status.HeaderText = "包厢状态";
            this.Status.Name = "Status";
            this.Status.ReadOnly = true;
            // 
            // ShutTime
            // 
            this.ShutTime.HeaderText = "关机时间";
            this.ShutTime.Name = "ShutTime";
            this.ShutTime.ReadOnly = true;
            // 
            // TimeLeft
            // 
            this.TimeLeft.HeaderText = "剩余时间";
            this.TimeLeft.Name = "TimeLeft";
            this.TimeLeft.ReadOnly = true;
            // 
            // Refresh
            // 
            this.Refresh.Location = new System.Drawing.Point(12, 415);
            this.Refresh.Name = "Refresh";
            this.Refresh.Size = new System.Drawing.Size(75, 23);
            this.Refresh.TabIndex = 1;
            this.Refresh.Text = "刷新(&R)";
            this.Refresh.UseVisualStyleBackColor = true;
            this.Refresh.Click += new System.EventHandler(this.Refresh_Click);
            // 
            // Cancel
            // 
            this.Cancel.ForeColor = System.Drawing.Color.Red;
            this.Cancel.Location = new System.Drawing.Point(441, 415);
            this.Cancel.Name = "Cancel";
            this.Cancel.Size = new System.Drawing.Size(75, 23);
            this.Cancel.TabIndex = 3;
            this.Cancel.Text = "关闭(&C)";
            this.Cancel.UseVisualStyleBackColor = true;
            this.Cancel.Click += new System.EventHandler(this.Cancel_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(93, 424);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(317, 12);
            this.label1.TabIndex = 4;
            this.label1.Text = "注: 双击相应行会执行相应操作。如下单、清理、延时等。";
            // 
            // MachineStateView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(530, 449);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.Cancel);
            this.Controls.Add(this.Refresh);
            this.Controls.Add(this.DataGrid);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "MachineStateView";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "包厢状态一览";
            this.Load += new System.EventHandler(this.MachineStateView_Load);
            ((System.ComponentModel.ISupportInitialize)(this.DataGrid)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView DataGrid;
        private System.Windows.Forms.Button Refresh;
        private System.Windows.Forms.Button Cancel;
        private System.Windows.Forms.DataGridViewTextBoxColumn MachineNo;
        private System.Windows.Forms.DataGridViewTextBoxColumn TypeName;
        private System.Windows.Forms.DataGridViewTextBoxColumn Status;
        private System.Windows.Forms.DataGridViewTextBoxColumn ShutTime;
        private System.Windows.Forms.DataGridViewTextBoxColumn TimeLeft;
        private System.Windows.Forms.Label label1;
    }
}