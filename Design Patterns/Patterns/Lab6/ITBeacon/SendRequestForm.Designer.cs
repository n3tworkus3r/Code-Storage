namespace ITBeacon
{
    partial class SendCmdForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(SendCmdForm));
            this.Request_TB = new System.Windows.Forms.TextBox();
            this.SendCmd_Button = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // Request_TB
            // 
            this.Request_TB.Location = new System.Drawing.Point(13, 13);
            this.Request_TB.Multiline = true;
            this.Request_TB.Name = "Request_TB";
            this.Request_TB.Size = new System.Drawing.Size(321, 204);
            this.Request_TB.TabIndex = 0;
            // 
            // SendCmd_Button
            // 
            this.SendCmd_Button.Location = new System.Drawing.Point(340, 173);
            this.SendCmd_Button.Name = "SendCmd_Button";
            this.SendCmd_Button.Size = new System.Drawing.Size(75, 34);
            this.SendCmd_Button.TabIndex = 1;
            this.SendCmd_Button.Text = "Отправить команду";
            this.SendCmd_Button.UseVisualStyleBackColor = true;
            this.SendCmd_Button.Click += new System.EventHandler(this.SendCmd_Button_Click);
            // 
            // SendCmdForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(433, 229);
            this.Controls.Add(this.SendCmd_Button);
            this.Controls.Add(this.Request_TB);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "SendCmdForm";
            this.Text = "Отправить команду";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.SendCmdForm_FormClosed);
            this.Load += new System.EventHandler(this.SendCmdForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox Request_TB;
        private System.Windows.Forms.Button SendCmd_Button;
    }
}