import java.awt.*;

public class FigureDecorator implements MyFigure
{
    MyFigure figure;
    public FigureDecorator(MyFigure figure){this.figure = figure;}
    @Override
    public void paint(Graphics2D g){figure.paint(g);}
}
