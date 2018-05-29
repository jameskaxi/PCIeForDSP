namespace PcieDriverTest
{
    partial class Form1
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
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle6 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle7 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle3 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle4 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle5 = new System.Windows.Forms.DataGridViewCellStyle();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.txtStatus = new System.Windows.Forms.RichTextBox();
            this.txtDmaFile = new System.Windows.Forms.TextBox();
            this.btnDmaFile = new System.Windows.Forms.Button();
            this.txtDmaTime = new System.Windows.Forms.TextBox();
            this.lalDmaTime = new System.Windows.Forms.Label();
            this.btnDmaLaun = new System.Windows.Forms.Button();
            this.bgwDmaTransfer = new System.ComponentModel.BackgroundWorker();
            this.label1 = new System.Windows.Forms.Label();
            this.timerDmaTransfer = new System.Windows.Forms.Timer(this.components);
            this.tipShow = new System.Windows.Forms.ToolTip(this.components);
            this.dgvRegWrite = new System.Windows.Forms.DataGridView();
            this.Column1 = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.Column2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column3 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column4 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.menuRegWrite = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.添加行ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.删除行ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.保存表格ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.载入表格ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.发送所有选中项ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.label2 = new System.Windows.Forms.Label();
            this.tboxBarX = new System.Windows.Forms.TextBox();
            this.btnDebugSet = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.tboxDebugAddr = new System.Windows.Forms.TextBox();
            this.tboxDebugData = new System.Windows.Forms.TextBox();
            this.btnDynamicLoad = new System.Windows.Forms.Button();
            this.tboxReadData = new System.Windows.Forms.TextBox();
            this.tboxReadAddr = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.btnReadFPGA = new System.Windows.Forms.Button();
            this.btnPreloading = new System.Windows.Forms.Button();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.btnDSPFile = new System.Windows.Forms.Button();
            this.tboxDSPFilePath = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.dgvRegWrite)).BeginInit();
            this.menuRegWrite.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.SuspendLayout();
            // 
            // txtStatus
            // 
            this.txtStatus.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            this.txtStatus.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txtStatus.Location = new System.Drawing.Point(16, 12);
            this.txtStatus.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.txtStatus.Name = "txtStatus";
            this.txtStatus.ReadOnly = true;
            this.txtStatus.Size = new System.Drawing.Size(310, 581);
            this.txtStatus.TabIndex = 0;
            this.txtStatus.Text = "";
            // 
            // txtDmaFile
            // 
            this.txtDmaFile.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            this.txtDmaFile.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txtDmaFile.Location = new System.Drawing.Point(13, 236);
            this.txtDmaFile.Name = "txtDmaFile";
            this.txtDmaFile.Size = new System.Drawing.Size(284, 24);
            this.txtDmaFile.TabIndex = 1;
            // 
            // btnDmaFile
            // 
            this.btnDmaFile.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(192)))), ((int)(((byte)(255)))));
            this.btnDmaFile.Font = new System.Drawing.Font("Verdana", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnDmaFile.Location = new System.Drawing.Point(304, 232);
            this.btnDmaFile.Name = "btnDmaFile";
            this.btnDmaFile.Size = new System.Drawing.Size(37, 33);
            this.btnDmaFile.TabIndex = 2;
            this.btnDmaFile.Text = "...";
            this.btnDmaFile.UseVisualStyleBackColor = false;
            this.btnDmaFile.Click += new System.EventHandler(this.btnDmaFile_Click);
            // 
            // txtDmaTime
            // 
            this.txtDmaTime.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            this.txtDmaTime.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txtDmaTime.Location = new System.Drawing.Point(133, 278);
            this.txtDmaTime.Name = "txtDmaTime";
            this.txtDmaTime.ReadOnly = true;
            this.txtDmaTime.Size = new System.Drawing.Size(91, 24);
            this.txtDmaTime.TabIndex = 3;
            this.txtDmaTime.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // lalDmaTime
            // 
            this.lalDmaTime.AutoSize = true;
            this.lalDmaTime.BackColor = System.Drawing.Color.Transparent;
            this.lalDmaTime.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lalDmaTime.Location = new System.Drawing.Point(30, 282);
            this.lalDmaTime.Name = "lalDmaTime";
            this.lalDmaTime.Size = new System.Drawing.Size(80, 15);
            this.lalDmaTime.TabIndex = 4;
            this.lalDmaTime.Text = "所花时间:";
            // 
            // btnDmaLaun
            // 
            this.btnDmaLaun.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(192)))), ((int)(((byte)(255)))));
            this.btnDmaLaun.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnDmaLaun.Location = new System.Drawing.Point(40, 334);
            this.btnDmaLaun.Name = "btnDmaLaun";
            this.btnDmaLaun.Size = new System.Drawing.Size(93, 33);
            this.btnDmaLaun.TabIndex = 5;
            this.btnDmaLaun.Text = "DMA发送";
            this.btnDmaLaun.UseVisualStyleBackColor = false;
            this.btnDmaLaun.Click += new System.EventHandler(this.btnDmaLaun_Click);
            // 
            // bgwDmaTransfer
            // 
            this.bgwDmaTransfer.DoWork += new System.ComponentModel.DoWorkEventHandler(this.bgwDmaTransfer_DoWork);
            this.bgwDmaTransfer.RunWorkerCompleted += new System.ComponentModel.RunWorkerCompletedEventHandler(this.bgwDmaTransfer_RunWorkerCompleted);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.Color.Transparent;
            this.label1.Font = new System.Drawing.Font("Calibri", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(228, 281);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(14, 18);
            this.label1.TabIndex = 6;
            this.label1.Text = "s";
            // 
            // timerDmaTransfer
            // 
            this.timerDmaTransfer.Interval = 500;
            this.timerDmaTransfer.Tick += new System.EventHandler(this.timerDmaTransfer_Tick);
            // 
            // tipShow
            // 
            this.tipShow.ShowAlways = true;
            // 
            // dgvRegWrite
            // 
            this.dgvRegWrite.AllowDrop = true;
            this.dgvRegWrite.AllowUserToResizeColumns = false;
            this.dgvRegWrite.AllowUserToResizeRows = false;
            this.dgvRegWrite.BackgroundColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            this.dgvRegWrite.ColumnHeadersBorderStyle = System.Windows.Forms.DataGridViewHeaderBorderStyle.Single;
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
            dataGridViewCellStyle1.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            this.dgvRegWrite.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this.dgvRegWrite.ColumnHeadersHeight = 30;
            this.dgvRegWrite.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.DisableResizing;
            this.dgvRegWrite.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Column1,
            this.Column2,
            this.Column3,
            this.Column4});
            this.dgvRegWrite.ContextMenuStrip = this.menuRegWrite;
            this.dgvRegWrite.EnableHeadersVisualStyles = false;
            this.dgvRegWrite.GridColor = System.Drawing.Color.Gold;
            this.dgvRegWrite.Location = new System.Drawing.Point(0, 0);
            this.dgvRegWrite.Name = "dgvRegWrite";
            dataGridViewCellStyle6.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle6.BackColor = System.Drawing.Color.Yellow;
            dataGridViewCellStyle6.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            dataGridViewCellStyle6.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle6.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle6.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle6.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.dgvRegWrite.RowHeadersDefaultCellStyle = dataGridViewCellStyle6;
            this.dgvRegWrite.RowHeadersVisible = false;
            this.dgvRegWrite.RowHeadersWidthSizeMode = System.Windows.Forms.DataGridViewRowHeadersWidthSizeMode.DisableResizing;
            dataGridViewCellStyle7.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle7.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            this.dgvRegWrite.RowsDefaultCellStyle = dataGridViewCellStyle7;
            this.dgvRegWrite.RowTemplate.Height = 27;
            this.dgvRegWrite.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dgvRegWrite.Size = new System.Drawing.Size(343, 551);
            this.dgvRegWrite.TabIndex = 8;
            this.dgvRegWrite.TabStop = false;
            this.dgvRegWrite.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dgvRegWrite_CellContentClick);
            this.dgvRegWrite.EditingControlShowing += new System.Windows.Forms.DataGridViewEditingControlShowingEventHandler(this.dgvRegWrite_EditingControlShowing);
            this.dgvRegWrite.DragDrop += new System.Windows.Forms.DragEventHandler(this.dgvRegWrite_DragDrop);
            this.dgvRegWrite.DragEnter += new System.Windows.Forms.DragEventHandler(this.dgvRegWrite_DragEnter);
            // 
            // Column1
            // 
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            dataGridViewCellStyle2.NullValue = false;
            dataGridViewCellStyle2.SelectionBackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            this.Column1.DefaultCellStyle = dataGridViewCellStyle2;
            this.Column1.HeaderText = "";
            this.Column1.Name = "Column1";
            this.Column1.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.Column1.Width = 30;
            // 
            // Column2
            // 
            dataGridViewCellStyle3.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle3.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            dataGridViewCellStyle3.Font = new System.Drawing.Font("Calibri", 10.8F, System.Drawing.FontStyle.Bold);
            dataGridViewCellStyle3.NullValue = "0x";
            dataGridViewCellStyle3.SelectionBackColor = System.Drawing.Color.Yellow;
            dataGridViewCellStyle3.SelectionForeColor = System.Drawing.Color.Black;
            this.Column2.DefaultCellStyle = dataGridViewCellStyle3;
            this.Column2.HeaderText = "物理地址";
            this.Column2.MaxInputLength = 34;
            this.Column2.Name = "Column2";
            this.Column2.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.Column2.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.Column2.Width = 115;
            // 
            // Column3
            // 
            dataGridViewCellStyle4.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle4.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            dataGridViewCellStyle4.Font = new System.Drawing.Font("Calibri", 10.8F, System.Drawing.FontStyle.Bold);
            dataGridViewCellStyle4.Format = "N0";
            dataGridViewCellStyle4.NullValue = "1";
            dataGridViewCellStyle4.SelectionBackColor = System.Drawing.Color.Yellow;
            dataGridViewCellStyle4.SelectionForeColor = System.Drawing.Color.Black;
            this.Column3.DefaultCellStyle = dataGridViewCellStyle4;
            this.Column3.HeaderText = "选中";
            this.Column3.Name = "Column3";
            this.Column3.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.Column3.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.Column3.Width = 87;
            // 
            // Column4
            // 
            dataGridViewCellStyle5.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle5.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            dataGridViewCellStyle5.Font = new System.Drawing.Font("Calibri", 10.8F, System.Drawing.FontStyle.Bold);
            dataGridViewCellStyle5.Format = "N0";
            dataGridViewCellStyle5.NullValue = "0";
            dataGridViewCellStyle5.SelectionBackColor = System.Drawing.Color.Yellow;
            dataGridViewCellStyle5.SelectionForeColor = System.Drawing.Color.Black;
            this.Column4.DefaultCellStyle = dataGridViewCellStyle5;
            this.Column4.HeaderText = "取消";
            this.Column4.Name = "Column4";
            this.Column4.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.Column4.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            this.Column4.Width = 87;
            // 
            // menuRegWrite
            // 
            this.menuRegWrite.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            this.menuRegWrite.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuRegWrite.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.添加行ToolStripMenuItem,
            this.删除行ToolStripMenuItem,
            this.保存表格ToolStripMenuItem,
            this.载入表格ToolStripMenuItem,
            this.发送所有选中项ToolStripMenuItem});
            this.menuRegWrite.Name = "ListWriteMenu";
            this.menuRegWrite.Size = new System.Drawing.Size(137, 114);
            // 
            // 添加行ToolStripMenuItem
            // 
            this.添加行ToolStripMenuItem.Name = "添加行ToolStripMenuItem";
            this.添加行ToolStripMenuItem.Size = new System.Drawing.Size(136, 22);
            this.添加行ToolStripMenuItem.Text = "添加行";
            this.添加行ToolStripMenuItem.Click += new System.EventHandler(this.添加行ToolStripMenuItem_Click);
            // 
            // 删除行ToolStripMenuItem
            // 
            this.删除行ToolStripMenuItem.Name = "删除行ToolStripMenuItem";
            this.删除行ToolStripMenuItem.Size = new System.Drawing.Size(136, 22);
            this.删除行ToolStripMenuItem.Text = "删除行";
            this.删除行ToolStripMenuItem.Click += new System.EventHandler(this.删除行ToolStripMenuItem_Click);
            // 
            // 保存表格ToolStripMenuItem
            // 
            this.保存表格ToolStripMenuItem.Name = "保存表格ToolStripMenuItem";
            this.保存表格ToolStripMenuItem.Size = new System.Drawing.Size(136, 22);
            this.保存表格ToolStripMenuItem.Text = "保存表格";
            this.保存表格ToolStripMenuItem.Click += new System.EventHandler(this.保存表格ToolStripMenuItem_Click);
            // 
            // 载入表格ToolStripMenuItem
            // 
            this.载入表格ToolStripMenuItem.Name = "载入表格ToolStripMenuItem";
            this.载入表格ToolStripMenuItem.Size = new System.Drawing.Size(136, 22);
            this.载入表格ToolStripMenuItem.Text = "载入表格";
            this.载入表格ToolStripMenuItem.Click += new System.EventHandler(this.载入表格ToolStripMenuItem_Click);
            // 
            // 发送所有选中项ToolStripMenuItem
            // 
            this.发送所有选中项ToolStripMenuItem.Name = "发送所有选中项ToolStripMenuItem";
            this.发送所有选中项ToolStripMenuItem.Size = new System.Drawing.Size(136, 22);
            this.发送所有选中项ToolStripMenuItem.Text = "发送所有项";
            this.发送所有选中项ToolStripMenuItem.Click += new System.EventHandler(this.发送所有选中项ToolStripMenuItem_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.BackColor = System.Drawing.Color.Transparent;
            this.label2.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label2.Location = new System.Drawing.Point(11, 38);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(34, 15);
            this.label2.TabIndex = 11;
            this.label2.Text = "bar";
            // 
            // tboxBarX
            // 
            this.tboxBarX.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            this.tboxBarX.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.tboxBarX.Location = new System.Drawing.Point(47, 33);
            this.tboxBarX.Name = "tboxBarX";
            this.tboxBarX.Size = new System.Drawing.Size(31, 24);
            this.tboxBarX.TabIndex = 10;
            this.tboxBarX.Text = "0";
            this.tboxBarX.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.tboxBarX.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tboxBarX_KeyPress);
            // 
            // btnDebugSet
            // 
            this.btnDebugSet.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(192)))), ((int)(((byte)(255)))));
            this.btnDebugSet.Font = new System.Drawing.Font("Verdana", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnDebugSet.Location = new System.Drawing.Point(97, 63);
            this.btnDebugSet.Name = "btnDebugSet";
            this.btnDebugSet.Size = new System.Drawing.Size(107, 33);
            this.btnDebugSet.TabIndex = 9;
            this.btnDebugSet.Text = "写";
            this.btnDebugSet.UseVisualStyleBackColor = false;
            this.btnDebugSet.Click += new System.EventHandler(this.btnDebugSet_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.BackColor = System.Drawing.Color.Transparent;
            this.label3.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label3.Location = new System.Drawing.Point(80, 40);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(43, 15);
            this.label3.TabIndex = 12;
            this.label3.Text = "addr";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.BackColor = System.Drawing.Color.Transparent;
            this.label4.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label4.Location = new System.Drawing.Point(197, 38);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(43, 15);
            this.label4.TabIndex = 13;
            this.label4.Text = "data";
            // 
            // tboxDebugAddr
            // 
            this.tboxDebugAddr.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            this.tboxDebugAddr.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.tboxDebugAddr.Location = new System.Drawing.Point(125, 33);
            this.tboxDebugAddr.Name = "tboxDebugAddr";
            this.tboxDebugAddr.Size = new System.Drawing.Size(70, 24);
            this.tboxDebugAddr.TabIndex = 14;
            this.tboxDebugAddr.Text = "1";
            this.tboxDebugAddr.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.tboxDebugAddr.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tboxDebugAddr_KeyPress);
            // 
            // tboxDebugData
            // 
            this.tboxDebugData.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            this.tboxDebugData.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.tboxDebugData.Location = new System.Drawing.Point(242, 33);
            this.tboxDebugData.Name = "tboxDebugData";
            this.tboxDebugData.Size = new System.Drawing.Size(65, 24);
            this.tboxDebugData.TabIndex = 15;
            this.tboxDebugData.Text = "1";
            this.tboxDebugData.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.tboxDebugData.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tboxDebugAddr_KeyPress);
            // 
            // btnDynamicLoad
            // 
            this.btnDynamicLoad.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(192)))), ((int)(((byte)(255)))));
            this.btnDynamicLoad.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnDynamicLoad.Location = new System.Drawing.Point(183, 334);
            this.btnDynamicLoad.Name = "btnDynamicLoad";
            this.btnDynamicLoad.Size = new System.Drawing.Size(93, 33);
            this.btnDynamicLoad.TabIndex = 16;
            this.btnDynamicLoad.Text = "动态加载";
            this.btnDynamicLoad.UseVisualStyleBackColor = false;
            this.btnDynamicLoad.Click += new System.EventHandler(this.btnDmaLaun_Click);
            // 
            // tboxReadData
            // 
            this.tboxReadData.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            this.tboxReadData.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.tboxReadData.Location = new System.Drawing.Point(225, 134);
            this.tboxReadData.Name = "tboxReadData";
            this.tboxReadData.Size = new System.Drawing.Size(65, 24);
            this.tboxReadData.TabIndex = 21;
            this.tboxReadData.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // tboxReadAddr
            // 
            this.tboxReadAddr.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            this.tboxReadAddr.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.tboxReadAddr.Location = new System.Drawing.Point(75, 134);
            this.tboxReadAddr.Name = "tboxReadAddr";
            this.tboxReadAddr.Size = new System.Drawing.Size(70, 24);
            this.tboxReadAddr.TabIndex = 20;
            this.tboxReadAddr.Text = "0x1";
            this.tboxReadAddr.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.tboxReadAddr.WordWrap = false;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.BackColor = System.Drawing.Color.Transparent;
            this.label5.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label5.Location = new System.Drawing.Point(174, 139);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(43, 15);
            this.label5.TabIndex = 19;
            this.label5.Text = "data";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.BackColor = System.Drawing.Color.Transparent;
            this.label6.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label6.Location = new System.Drawing.Point(30, 139);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(43, 15);
            this.label6.TabIndex = 18;
            this.label6.Text = "addr";
            // 
            // btnReadFPGA
            // 
            this.btnReadFPGA.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(192)))), ((int)(((byte)(255)))));
            this.btnReadFPGA.Font = new System.Drawing.Font("Verdana", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnReadFPGA.Location = new System.Drawing.Point(83, 174);
            this.btnReadFPGA.Name = "btnReadFPGA";
            this.btnReadFPGA.Size = new System.Drawing.Size(141, 33);
            this.btnReadFPGA.TabIndex = 17;
            this.btnReadFPGA.Text = "读";
            this.btnReadFPGA.UseVisualStyleBackColor = false;
            this.btnReadFPGA.Click += new System.EventHandler(this.btnReadFPGA_Click);
            // 
            // btnPreloading
            // 
            this.btnPreloading.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(192)))), ((int)(((byte)(255)))));
            this.btnPreloading.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnPreloading.Location = new System.Drawing.Point(97, 489);
            this.btnPreloading.Name = "btnPreloading";
            this.btnPreloading.Size = new System.Drawing.Size(143, 44);
            this.btnPreloading.TabIndex = 22;
            this.btnPreloading.Text = "预加载";
            this.btnPreloading.UseVisualStyleBackColor = false;
            this.btnPreloading.Click += new System.EventHandler(this.btnPreloading_Click);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Location = new System.Drawing.Point(342, 12);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(354, 582);
            this.tabControl1.TabIndex = 23;
            // 
            // tabPage1
            // 
            this.tabPage1.BackColor = System.Drawing.Color.PaleGoldenrod;
            this.tabPage1.Controls.Add(this.btnDSPFile);
            this.tabPage1.Controls.Add(this.tboxDSPFilePath);
            this.tabPage1.Controls.Add(this.tboxDebugData);
            this.tabPage1.Controls.Add(this.btnDebugSet);
            this.tabPage1.Controls.Add(this.btnPreloading);
            this.tabPage1.Controls.Add(this.tboxBarX);
            this.tabPage1.Controls.Add(this.btnDynamicLoad);
            this.tabPage1.Controls.Add(this.tboxReadData);
            this.tabPage1.Controls.Add(this.btnDmaLaun);
            this.tabPage1.Controls.Add(this.tboxReadAddr);
            this.tabPage1.Controls.Add(this.label1);
            this.tabPage1.Controls.Add(this.label2);
            this.tabPage1.Controls.Add(this.label5);
            this.tabPage1.Controls.Add(this.lalDmaTime);
            this.tabPage1.Controls.Add(this.label3);
            this.tabPage1.Controls.Add(this.txtDmaTime);
            this.tabPage1.Controls.Add(this.label6);
            this.tabPage1.Controls.Add(this.btnDmaFile);
            this.tabPage1.Controls.Add(this.label4);
            this.tabPage1.Controls.Add(this.txtDmaFile);
            this.tabPage1.Controls.Add(this.btnReadFPGA);
            this.tabPage1.Controls.Add(this.tboxDebugAddr);
            this.tabPage1.Location = new System.Drawing.Point(4, 24);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(346, 554);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "tabPage1";
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.dgvRegWrite);
            this.tabPage2.Location = new System.Drawing.Point(4, 24);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(346, 554);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "tabPage2";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // btnDSPFile
            // 
            this.btnDSPFile.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(192)))), ((int)(((byte)(255)))));
            this.btnDSPFile.Font = new System.Drawing.Font("Verdana", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnDSPFile.Location = new System.Drawing.Point(297, 438);
            this.btnDSPFile.Name = "btnDSPFile";
            this.btnDSPFile.Size = new System.Drawing.Size(37, 33);
            this.btnDSPFile.TabIndex = 24;
            this.btnDSPFile.Text = "...";
            this.btnDSPFile.UseVisualStyleBackColor = false;
            this.btnDSPFile.Click += new System.EventHandler(this.btnDSPFile_Click);
            // 
            // tboxDSPFilePath
            // 
            this.tboxDSPFilePath.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            this.tboxDSPFilePath.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.tboxDSPFilePath.Location = new System.Drawing.Point(6, 442);
            this.tboxDSPFilePath.Name = "tboxDSPFilePath";
            this.tboxDSPFilePath.Size = new System.Drawing.Size(284, 24);
            this.tboxDSPFilePath.TabIndex = 23;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 14F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ClientSize = new System.Drawing.Size(707, 606);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.txtStatus);
            this.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Pcie驱动测试";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dgvRegWrite)).EndInit();
            this.menuRegWrite.ResumeLayout(false);
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            this.tabPage2.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.RichTextBox txtStatus;
        private System.Windows.Forms.TextBox txtDmaFile;
        private System.Windows.Forms.Button btnDmaFile;
        private System.Windows.Forms.TextBox txtDmaTime;
        private System.Windows.Forms.Label lalDmaTime;
        private System.Windows.Forms.Button btnDmaLaun;
        private System.ComponentModel.BackgroundWorker bgwDmaTransfer;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Timer timerDmaTransfer;
        private System.Windows.Forms.ToolTip tipShow;
        private System.Windows.Forms.DataGridView dgvRegWrite;
        private System.Windows.Forms.ContextMenuStrip menuRegWrite;
        private System.Windows.Forms.ToolStripMenuItem 保存表格ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 载入表格ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 添加行ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 删除行ToolStripMenuItem;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox tboxBarX;
        private System.Windows.Forms.Button btnDebugSet;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox tboxDebugAddr;
        private System.Windows.Forms.TextBox tboxDebugData;
        private System.Windows.Forms.Button btnDynamicLoad;
        private System.Windows.Forms.ToolStripMenuItem 发送所有选中项ToolStripMenuItem;
        private System.Windows.Forms.TextBox tboxReadData;
        private System.Windows.Forms.TextBox tboxReadAddr;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button btnReadFPGA;
        private System.Windows.Forms.DataGridViewCheckBoxColumn Column1;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column2;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column3;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column4;
        private System.Windows.Forms.Button btnPreloading;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.Button btnDSPFile;
        private System.Windows.Forms.TextBox tboxDSPFilePath;
    }
}

