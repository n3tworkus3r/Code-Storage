using System.Collections.Generic;
using System.Linq;
using Xamarin.Forms;
namespace CGI.Views
{
    public partial class AboutPage : ContentPage
    {
        private static IEnumerable<Picker> _pickers;
        private static readonly SkiaSharp.Views.Forms.SKCanvasView _sKCanvasView = new()
        {
            HeightRequest = 500,
            VerticalOptions = LayoutOptions.Fill,
            HorizontalOptions = LayoutOptions.Fill
        };
        private static class MosaicArgs
        {
            static public SkiaSharp.SKColor[] Colors { get; set; } = new SkiaSharp.SKColor[4];
            static public double Width { get; set; }
            static public double Height { get; set; }
            static public int BlockSize { get; set; }
        }
        public AboutPage()
        {
            InitializeComponent();
            _sKCanvasView.PaintSurface += CanvasView_PaintSurface;
            var pickersFlexLayout = new FlexLayout();
            _pickers = Pickers().ToArray();
            foreach (var picker in _pickers)
            {
                picker.SelectedIndexChanged += Picker_SelectedIndexChanged;
                pickersFlexLayout.Children.Add(picker);
            }
            Content = new StackLayout()
            {
                Children =
                {
                    pickersFlexLayout,
                    _sKCanvasView
                }
            };
            SetMosaicColors();
        }
        private void Picker_SelectedIndexChanged(object sender, System.EventArgs e)
        {
            SetMosaicColors();
            _sKCanvasView.InvalidateSurface();
        }
        private void SetMosaicColors()
        {
            MosaicArgs.BlockSize = System.Convert.ToInt32(_pickers.ElementAt(4).SelectedItem);
            for (int i = 0; i < 4; i++)
                MosaicArgs.Colors[i] = SkiaSharp.Views.Desktop.Extensions.ToSKColor(System.Drawing.Color.FromName(_pickers.ElementAt(i).SelectedItem.ToString()));
        }
        private IEnumerable<Picker> Pickers()
        {
            var colors = "BlueViolet LightPink CornflowerBlue GreenYellow".Split(' ');
            var pickerColors = typeof(SkiaSharp.SKColors).GetFields().Select(el => el.Name).ToList();
            for (int i = 0; i < MosaicArgs.Colors.Length; i++)
                yield return new Picker()
                {
                    ItemsSource = pickerColors,
                    SelectedIndex = pickerColors.IndexOf(colors[i]),
                    Title = $"Color{i}",
                    WidthRequest = 80
                };
            yield return new Picker()
            {
                ItemsSource = "2 4 8".Split(' '),
                SelectedIndex = 2,
                Title = "Size",
                WidthRequest = 80
            };
        }
        private void CanvasView_PaintSurface(object sender, SkiaSharp.Views.Forms.SKPaintSurfaceEventArgs e)
        {
            MosaicArgs.Width = e.Info.Width;
            MosaicArgs.Height = e.Info.Height;
            var blockColor = MosaicArgs.Colors[new System.Random().Next(MosaicArgs.Colors.Length)];
            for (int i = 0; i < MosaicArgs.Height; i += MosaicArgs.BlockSize)
                for (int j = 0; j < MosaicArgs.Width; j += MosaicArgs.BlockSize, blockColor = MosaicArgs.Colors[new System.Random().Next(MosaicArgs.Colors.Length)])
                    for (int ik = 0; ik < MosaicArgs.BlockSize; ik++)
                        for (int jk = 0; jk < MosaicArgs.BlockSize; jk++)
                            e.Surface.Canvas.DrawPoint(new SkiaSharp.SKPoint(i + ik, j + jk), new SkiaSharp.SKPaint() { Color = blockColor });
        }
    }
}
