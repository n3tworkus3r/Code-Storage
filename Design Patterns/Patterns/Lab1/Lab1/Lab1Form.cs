using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace Lab1
{
    public partial class Lab1Form : Form
    {
        public readonly string filePath = "text.xml";
        public Lab1Form() => InitializeComponent();
        private void Lab1Form_Paint(object sender, PaintEventArgs e)
        {
            Logic.SerializeObjects(this);
            Dictionary<FigType, Action<DrawableFigure, Graphics>> dict = new()
            {
                [FigType.Rectangle] = (DrawableFigure fig, Graphics g) => e.Graphics.FillRectangle(new SolidBrush(Color.FromArgb(150, fig.FigColor)), (Rectangle)fig.Figure),
                [FigType.Ellipse] = (DrawableFigure fig, Graphics g) => e.Graphics.FillEllipse(new SolidBrush(Color.FromArgb(150, fig.FigColor)), (Rectangle)fig.Figure)
            };
            using System.IO.StreamReader sr = new(filePath);
            var figures = new System.Xml.Serialization.XmlSerializer(typeof(DrawableFigures)).Deserialize(sr) as DrawableFigures;
            foreach (var fig in figures)
                dict[fig.FigName](fig, e.Graphics);
        }
    }
    public static class Logic
    {
        public static void SerializeObjects(Lab1Form form)
        {
            Random rand = new();
            using System.IO.StreamWriter sw = new(form.filePath);
            DrawableFigures figures = new();
            for (int i = 0; i < 10; i++)
            {
                var temp = (FigType)new Random().Next(Enum.GetNames(typeof(FigType)).Length);
                figures.Add(temp switch
                {
                    FigType.Rectangle or FigType.Ellipse => new DrawableFigure(Color.FromArgb(100, rand.Next(255), rand.Next(255), rand.Next(255)), temp, new Rectangle(rand.Next(form.Width / 2), rand.Next(form.Height / 2), rand.Next(form.Width / 2), rand.Next(form.Height / 2))),
                    _ => throw new NotImplementedException()
                }
                    );
            }
            new System.Xml.Serialization.XmlSerializer(typeof(DrawableFigures)).Serialize(sw, figures);
        }
    }
}
