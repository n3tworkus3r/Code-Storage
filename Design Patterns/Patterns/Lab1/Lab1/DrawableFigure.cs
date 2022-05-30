using System;
using System.Drawing;
using System.Xml.Serialization;

namespace Lab1
{
    public enum FigType
    {
        Rectangle,
        Ellipse
    }
    [Serializable]
    [XmlInclude(typeof(Rectangle))]
    public class DrawableFigure
    {
        public int Layer { get; set; }
        public FigType FigName { get; set; }
        public object Figure { get; set; }
        [XmlIgnore]
        public Color FigColor { get; set; }

        [XmlElement("FigColor")]
        public int FigColorAsArgb { get => FigColor.ToArgb(); set => FigColor = Color.FromArgb(value); }

        public FigType FigType
        {
            get => default;
            set
            {
            }
        }

        public DrawableFigure(){}
        public DrawableFigure(Color color, FigType figName, object figure)
        {
            FigColor= color;
            FigName = figName;
            Figure = figure;
        }
    }
    [Serializable]
    public class DrawableFigures : System.Collections.Generic.List<DrawableFigure>
    {
        public DrawableFigure DrawableFigure
        {
            get => default;
            set
            {
            }
        }
    }
}
