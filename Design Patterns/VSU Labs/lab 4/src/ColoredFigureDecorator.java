import java.awt.*;

public class ColoredFigureDecorator extends FigureDecorator
{
    Colour colour;
    public ColoredFigureDecorator(Colour colour, MyFigure figure)
    {
        super(figure);
        this.colour = colour;
    }
    @Override
    public void paint(Graphics2D g)
    {
        colour.paint(g);
        super.paint(g);
    }
}
