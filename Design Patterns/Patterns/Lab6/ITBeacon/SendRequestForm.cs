using System;
using System.Data.SqlClient;
using System.Windows.Forms;

namespace ITBeacon
{
    public partial class SendCmdForm : Form
    {
        public MainForm PrevForm { get; set; }
        public SendCmdForm(MainForm mainForm)
        {
            InitializeComponent();
            PrevForm = mainForm;
        }
        void SendCmd_Button_Click(object sender, EventArgs e)
        {
            try
            {
                new SqlCommand(Request_TB.Text) { Connection = SqlConnectionHandler.Lazy.Connection }.ExecuteNonQuery();
                MessageBox.Show("Успешно");
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        void SendCmdForm_Load(object sender, EventArgs e)
        {
            BackColor = PrevForm.BackColor;
        }
        void SendCmdForm_FormClosed(object sender, FormClosedEventArgs e)
            => PrevForm.FillTableList();
    }
}
