namespace 前台系统
{
    partial class SearchFreeMachineForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(SearchFreeMachineForm));
            this.label1 = new System.Windows.Forms.Label();
            this.TypeSelect = new System.Windows.Forms.ComboBox();
            this.Search = new System.Windows.Forms.Button();
            this.Results = new System.Windows.Forms.ListBox();
            this.PricesTitle = new System.Windows.Forms.Label();
            this.Prices = new System.Windows.Forms.Label();
            this.ResultCount = new System.Windows.Forms.Label();
            this.Record = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 13);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(59, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "包厢类型:";
            // 
            // TypeSelect
            // 
            this.TypeSelect.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.TypeSelect.FormattingEnabled = true;
            this.TypeSelect.Items.AddRange(new object[] {
            "获取中..."});
            this.TypeSelect.Location = new System.Drawing.Point(78, 10);
            this.TypeSelect.Name = "TypeSelect";
            this.TypeSelect.Size = new System.Drawing.Size(176, 20);
            this.TypeSelect.TabIndex = 1;
            this.TypeSelect.SelectedIndexChanged += new System.EventHandler(this.TypeSelect_SelectedIndexChanged);
            // 
            // Search
            // 
            this.Search.Location = new System.Drawing.Point(260, 8);
            this.Search.Name = "Search";
            this.Search.Size = new System.Drawing.Size(75, 23);
            this.Search.TabIndex = 2;
            this.Search.Text = "查找(&S)";
            this.Search.UseVisualStyleBackColor = true;
            this.Search.Click += new System.EventHandler(this.Search_Click);
            // 
            // Results
            // 
            this.Results.FormattingEnabled = true;
            this.Results.ItemHeight = 12;
            this.Results.Location = new System.Drawing.Point(15, 48);
            this.Results.Name = "Results";
            this.Results.Size = new System.Drawing.Size(162, 232);
            this.Results.TabIndex = 3;
            // 
            // PricesTitle
            // 
            this.PricesTitle.AutoSize = true;
            this.PricesTitle.Location = new System.Drawing.Point(195, 48);
            this.PricesTitle.Name = "PricesTitle";
            this.PricesTitle.Size = new System.Drawing.Size(71, 12);
            this.PricesTitle.TabIndex = 4;
            this.PricesTitle.Text = "❀ 价格一览\r\n";
            // 
            // Prices
            // 
            this.Prices.AutoSize = true;
            this.Prices.Cursor = System.Windows.Forms.Cursors.No;
            this.Prices.ForeColor = System.Drawing.Color.Red;
            this.Prices.Location = new System.Drawing.Point(197, 64);
            this.Prices.Name = "Prices";
            this.Prices.Size = new System.Drawing.Size(11, 12);
            this.Prices.TabIndex = 5;
            this.Prices.Text = "";
            // 
            // ResultCount
            // 
            this.ResultCount.AutoSize = true;
            this.ResultCount.Location = new System.Drawing.Point(197, 255);
            this.ResultCount.Name = "ResultCount";
            this.ResultCount.Size = new System.Drawing.Size(0, 12);
            this.ResultCount.TabIndex = 6;
            // 
            // Record
            // 
            this.Record.Location = new System.Drawing.Point(193, 217);
            this.Record.Name = "Record";
            this.Record.Size = new System.Drawing.Size(142, 32);
            this.Record.TabIndex = 7;
            this.Record.Text = "下单(&O)";
            this.Record.UseVisualStyleBackColor = true;
            this.Record.Click += new System.EventHandler(this.Record_Click);
            // 
            // SearchFreeMachineForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(350, 297);
            this.Controls.Add(this.Record);
            this.Controls.Add(this.ResultCount);
            this.Controls.Add(this.Prices);
            this.Controls.Add(this.PricesTitle);
            this.Controls.Add(this.Results);
            this.Controls.Add(this.Search);
            this.Controls.Add(this.TypeSelect);
            this.Controls.Add(this.label1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "SearchFreeMachineForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "查找空闲包厢";
            this.Load += new System.EventHandler(this.SearchFreeMachineForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox TypeSelect;
        private System.Windows.Forms.Button Search;
        private System.Windows.Forms.ListBox Results;
        private System.Windows.Forms.Label PricesTitle;
        private System.Windows.Forms.Label Prices;
        private System.Windows.Forms.Label ResultCount;
        private System.Windows.Forms.Button Record;
    }
}