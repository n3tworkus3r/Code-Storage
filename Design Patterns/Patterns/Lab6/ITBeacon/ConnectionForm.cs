using System;
using System.Windows.Forms;

namespace ITBeacon
{
    public partial class ConnectionForm : Form
    {
        public MainForm PrevForm { get; set; }
        public ConnectionForm(MainForm mainForm)
        {
            InitializeComponent();
            PrevForm = mainForm;
        }
        void Connect_Button_Click(object sender, EventArgs e)
        {
            try
            {
                SqlConnectionHandler.Lazy.Connection = new(ConnectionString_TB.Text);
                SqlConnectionHandler.Lazy.Connection.Open();
                PrevForm.FillTableList();
                PrevForm.Show();
                Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        void Exit_Button_Click(object sender, EventArgs e) => Close();
    }
}
