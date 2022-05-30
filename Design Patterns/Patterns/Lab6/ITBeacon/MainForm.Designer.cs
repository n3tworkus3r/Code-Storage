namespace ITBeacon
{
    partial class MainForm
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.DBCreation_Button = new System.Windows.Forms.Button();
            this.SendRequest_Button = new System.Windows.Forms.Button();
            this.Metadata_DGV = new System.Windows.Forms.DataGridView();
            this.SubmitChanges_Button = new System.Windows.Forms.Button();
            this.RemoveEl_Button = new System.Windows.Forms.Button();
            this.Tables_LB = new System.Windows.Forms.ListBox();
            this.ChangeConnection_Button = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.Metadata_DGV)).BeginInit();
            this.SuspendLayout();
            // 
            // DBCreation_Button
            // 
            this.DBCreation_Button.Enabled = false;
            this.DBCreation_Button.Location = new System.Drawing.Point(642, 351);
            this.DBCreation_Button.Name = "DBCreation_Button";
            this.DBCreation_Button.Size = new System.Drawing.Size(121, 23);
            this.DBCreation_Button.TabIndex = 0;
            this.DBCreation_Button.Text = "Создать Таблицы";
            this.DBCreation_Button.UseVisualStyleBackColor = true;
            this.DBCreation_Button.Click += new System.EventHandler(this.DBCreation_Button_Click);
            // 
            // SendRequest_Button
            // 
            this.SendRequest_Button.Location = new System.Drawing.Point(497, 351);
            this.SendRequest_Button.Name = "SendRequest_Button";
            this.SendRequest_Button.Size = new System.Drawing.Size(121, 23);
            this.SendRequest_Button.TabIndex = 1;
            this.SendRequest_Button.Text = "Создать Запрос";
            this.SendRequest_Button.UseVisualStyleBackColor = true;
            this.SendRequest_Button.Click += new System.EventHandler(this.SendRequest_Button_Click);
            // 
            // Metadata_DGV
            // 
            this.Metadata_DGV.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.Metadata_DGV.Location = new System.Drawing.Point(13, 13);
            this.Metadata_DGV.Name = "Metadata_DGV";
            this.Metadata_DGV.Size = new System.Drawing.Size(605, 317);
            this.Metadata_DGV.TabIndex = 2;
            this.Metadata_DGV.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.Metadata_DGV_CellValueChanged);
            // 
            // SubmitChanges_Button
            // 
            this.SubmitChanges_Button.Enabled = false;
            this.SubmitChanges_Button.Location = new System.Drawing.Point(13, 351);
            this.SubmitChanges_Button.Name = "SubmitChanges_Button";
            this.SubmitChanges_Button.Size = new System.Drawing.Size(156, 23);
            this.SubmitChanges_Button.TabIndex = 3;
            this.SubmitChanges_Button.Text = "Подтвердить изменения";
            this.SubmitChanges_Button.UseVisualStyleBackColor = true;
            this.SubmitChanges_Button.Click += new System.EventHandler(this.SubmitChanges_Button_Click);
            // 
            // RemoveEl_Button
            // 
            this.RemoveEl_Button.Location = new System.Drawing.Point(187, 351);
            this.RemoveEl_Button.Name = "RemoveEl_Button";
            this.RemoveEl_Button.Size = new System.Drawing.Size(75, 23);
            this.RemoveEl_Button.TabIndex = 6;
            this.RemoveEl_Button.Text = "Удалить";
            this.RemoveEl_Button.UseVisualStyleBackColor = true;
            this.RemoveEl_Button.Click += new System.EventHandler(this.RemoveEl_Button_Click);
            // 
            // Tables_LB
            // 
            this.Tables_LB.FormattingEnabled = true;
            this.Tables_LB.Location = new System.Drawing.Point(642, 13);
            this.Tables_LB.Name = "Tables_LB";
            this.Tables_LB.Size = new System.Drawing.Size(121, 316);
            this.Tables_LB.TabIndex = 7;
            this.Tables_LB.SelectedIndexChanged += new System.EventHandler(this.Tables_LB_SelectedIndexChanged);
            // 
            // ChangeConnection_Button
            // 
            this.ChangeConnection_Button.Location = new System.Drawing.Point(298, 351);
            this.ChangeConnection_Button.Name = "ChangeConnection_Button";
            this.ChangeConnection_Button.Size = new System.Drawing.Size(152, 23);
            this.ChangeConnection_Button.TabIndex = 8;
            this.ChangeConnection_Button.Text = "Изменить подключение";
            this.ChangeConnection_Button.UseVisualStyleBackColor = true;
            this.ChangeConnection_Button.Click += new System.EventHandler(this.ChangeConnection_Button_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.BackColor = System.Drawing.Color.DimGray;
            this.ClientSize = new System.Drawing.Size(784, 411);
            this.Controls.Add(this.ChangeConnection_Button);
            this.Controls.Add(this.Tables_LB);
            this.Controls.Add(this.RemoveEl_Button);
            this.Controls.Add(this.SubmitChanges_Button);
            this.Controls.Add(this.Metadata_DGV);
            this.Controls.Add(this.SendRequest_Button);
            this.Controls.Add(this.DBCreation_Button);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "MainForm";
            this.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "ControlPanel";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.MainPage_Close);
            ((System.ComponentModel.ISupportInitialize)(this.Metadata_DGV)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button DBCreation_Button;
        private System.Windows.Forms.Button SendRequest_Button;
        private System.Windows.Forms.DataGridView Metadata_DGV;
        private System.Windows.Forms.Button SubmitChanges_Button;
        private System.Windows.Forms.Button RemoveEl_Button;
        private System.Windows.Forms.ListBox Tables_LB;
        private System.Windows.Forms.Button ChangeConnection_Button;
    }
}

