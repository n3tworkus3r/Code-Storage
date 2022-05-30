using CGI.ViewModels;
using System.ComponentModel;
using Xamarin.Forms;

namespace CGI.Views
{
    public partial class ItemDetailPage : ContentPage
    {
        public ItemDetailPage()
        {
            InitializeComponent();
            BindingContext = new ItemDetailViewModel();
        }
    }
}