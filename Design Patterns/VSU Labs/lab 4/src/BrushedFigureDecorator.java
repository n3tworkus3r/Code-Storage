import java.awt.*;

public class BrushedFigureDecorator extends FigureDecorator
{
    Stroke stroke;
    public BrushedFigureDecorator(Stroke stroke, MyFigure myFigure){
        super(myFigure);
        this.stroke = stroke;
    }

    @Override
    public void paint(Graphics2D g)
    {
        stroke.paint(g);
        super.paint(g);
    }
}
