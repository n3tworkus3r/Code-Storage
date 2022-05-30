import java.awt.Color;
import java.util.ArrayList;
import java.util.Collection;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

public class Runner {
	public static void main(String[] args) throws ClassNotFoundException, InstantiationException, IllegalAccessException, UnsupportedLookAndFeelException {
		Collection<MyFigure> figures = new ArrayList<>();
		figures.add(new LinearGradient(new Line(new Point(0, 250), new Point(0, 350)), new Color(0, 128, 255), new Color(0, 0, 128)));
		figures.add(new Rectangle(new Point(275, 300), 550, 100));
		figures.add(new ColoredFigureDecorator(new Colour(Color.YELLOW), new Circle(new Point(450, 50), 25)));
		figures.add(new BrushedFigureDecorator(new Stroke(2), new ColoredFigureDecorator(new Colour(Color.ORANGE), new Line(new Point(200, 25), new Point(200, 125)))));
		figures.add(new BrushedFigureDecorator(new Stroke(2), new ColoredFigureDecorator(new Colour(Color.ORANGE),new Line(new Point(175, 50), new Point(225, 50)))));
		figures.add(new BrushedFigureDecorator(new Stroke(2), new ColoredFigureDecorator(new Colour(Color.BLACK), new Polyline(new Point(50, 200), new Point(200, 50), new Point(500, 200)))));
		figures.add(new ColoredFigureDecorator(new Colour(new Color(255, 200, 200)), new Rectangle(new Point(225, 175), 150, 50)));
		figures.add(new BrushedFigureDecorator(new Stroke(1), new ColoredFigureDecorator(new Colour(Color.RED),new RectangleBorder(new Point(225, 175), 150, 50))));
		figures.add(new ColoredFigureDecorator(new Colour(new Color(255, 200, 200)), new Rectangle(new Point(212, 137), 75, 25)));
		figures.add(new ColoredFigureDecorator(new Colour(Color.RED),new RectangleBorder(new Point(212, 137), 75, 25)));
		figures.add(new ColoredFigureDecorator(new Colour(new Color(0, 128, 0)),new BrushedFigureDecorator(new Stroke(1),new Point(175, 175))));
		figures.add(new ColoredFigureDecorator(new Colour(new Color(0, 128, 0)),new Point(200, 175)));
		figures.add(new ColoredFigureDecorator(new Colour(new Color(0, 128, 0)),new Point(225, 175)));
		figures.add(new ColoredFigureDecorator(new Colour(new Color(0, 128, 0)), new Point(250, 175)));
		figures.add(new ColoredFigureDecorator(new Colour(new Color(0, 128, 0)), new Point(275, 175)));
		figures.add(new ColoredFigureDecorator(new Colour(Color.LIGHT_GRAY),new Polygon(new Point(50, 200), new Point(500, 200), new Point(400, 300), new Point(150, 300))));
		figures.add(new BrushedFigureDecorator(new Stroke(2), new ColoredFigureDecorator( new Colour(Color.GRAY), new Polyline(new Point(50, 200), new Point(500, 200), new Point(400, 300), new Point(150, 300), new Point(50, 200)))));
		figures.add(new RadialGradient(new Circle(new Point(175, 250), 25), Color.CYAN, Color.WHITE));
		figures.add(new Circle(new Point(175, 250), 25));
		figures.add(new BrushedFigureDecorator(new Stroke(3),new ColoredFigureDecorator(new Colour(Color.MAGENTA), new CircleBorder(new Point(175, 250), 25))));
		figures.add(new RadialGradient(new Circle(new Point(275, 250), 25), Color.CYAN, Color.WHITE));
		figures.add(new Circle(new Point(275, 250), 25));
		figures.add(new BrushedFigureDecorator(new Stroke(3), new ColoredFigureDecorator(new Colour(Color.MAGENTA),new CircleBorder(new Point(275, 250), 25))));
		figures.add(new RadialGradient(new Circle(new Point(375, 250), 25), Color.CYAN, Color.WHITE));
		figures.add(new Circle(new Point(375, 250), 25));
		figures.add(new BrushedFigureDecorator(new Stroke(3),new ColoredFigureDecorator(new Colour(Color.MAGENTA),new CircleBorder(new Point(375, 250), 25))));
		UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		new MainFrame("Рисунок", 550, 350, new Picture(figures));
	}
}
