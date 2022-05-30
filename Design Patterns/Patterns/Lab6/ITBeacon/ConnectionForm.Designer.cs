namespace ITBeacon
{
    partial class ConnectionForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ConnectionForm));
            this.Connect_Button = new System.Windows.Forms.Button();
            this.Exit_Button = new System.Windows.Forms.Button();
            this.EnterStr_Label = new System.Windows.Forms.Label();
            this.ConnectionString_TB = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // Connect_Button
            // 
            this.Connect_Button.Location = new System.Drawing.Point(12, 62);
            this.Connect_Button.Name = "Connect_Button";
            this.Connect_Button.Size = new System.Drawing.Size(97, 23);
            this.Connect_Button.TabIndex = 0;
            this.Connect_Button.Text = "Подключиться";
            this.Connect_Button.UseVisualStyleBackColor = true;
            this.Connect_Button.Click += new System.EventHandler(this.Connect_Button_Click);
            // 
            // Exit_Button
            // 
            this.Exit_Button.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.Exit_Button.Location = new System.Drawing.Point(157, 62);
            this.Exit_Button.Name = "Exit_Button";
            this.Exit_Button.Size = new System.Drawing.Size(75, 23);
            this.Exit_Button.TabIndex = 1;
            this.Exit_Button.Text = "Выйти";
            this.Exit_Button.UseVisualStyleBackColor = true;
            this.Exit_Button.Click += new System.EventHandler(this.Exit_Button_Click);
            // 
            // EnterStr_Label
            // 
            this.EnterStr_Label.AutoSize = true;
            this.EnterStr_Label.ForeColor = System.Drawing.Color.White;
            this.EnterStr_Label.Location = new System.Drawing.Point(34, 9);
            this.EnterStr_Label.Name = "EnterStr_Label";
            this.EnterStr_Label.Size = new System.Drawing.Size(184, 13);
            this.EnterStr_Label.TabIndex = 2;
            this.EnterStr_Label.Text = "Введите строку подключения к БД";
            // 
            // ConnectionString_TB
            // 
            this.ConnectionString_TB.Location = new System.Drawing.Point(12, 25);
            this.ConnectionString_TB.Name = "ConnectionString_TB";
            this.ConnectionString_TB.Size = new System.Drawing.Size(220, 20);
            this.ConnectionString_TB.TabIndex = 3;
            this.ConnectionString_TB.Text = "Data Source=localhost;Initial Catalog=DreamHome;Integrated Security=True";
            // 
            // ConnectionForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.DimGray;
            this.ClientSize = new System.Drawing.Size(244, 106);
            this.Controls.Add(this.ConnectionString_TB);
            this.Controls.Add(this.EnterStr_Label);
            this.Controls.Add(this.Exit_Button);
            this.Controls.Add(this.Connect_Button);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "ConnectionForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "ConnectionForm";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button Connect_Button;
        private System.Windows.Forms.Button Exit_Button;
        private System.Windows.Forms.Label EnterStr_Label;
        private System.Windows.Forms.TextBox ConnectionString_TB;
    }
}