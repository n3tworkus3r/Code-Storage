import java.awt.Color;
import java.util.ArrayList;
import java.util.Collection;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

public class Runner {
	public static void main(String[] args) throws ClassNotFoundException, InstantiationException, IllegalAccessException, UnsupportedLookAndFeelException {
		Collection<MyFigure> figures = new ArrayList<>();

		// GRASS
		figures.add(new LinearGradient(new Line(new Point(0, 250), new Point(0, 350)), new Color(0, 128, 128), new Color(0, 128, 0)));
		figures.add(new Rectangle(new Point(275, 300), 550, 100));

		// HOME BODY
		figures.add(new BrushedFigureDecorator(new Stroke(3), new ColoredFigureDecorator(new Colour(Color.BLACK),new RectangleBorder(new Point(225, 175), 250, 150))));
		figures.add(new ColoredFigureDecorator(new Colour(new Color(155, 100, 100)), new Rectangle(new Point(225, 175), 250, 150)));

		// SUN
		figures.add(new ColoredFigureDecorator(new Colour(Color.YELLOW), new Circle(new Point(450, 50), 25)));


		// WINDOW 1
		figures.add(new ColoredFigureDecorator(new Colour(new Color(0, 200, 200)), new Rectangle(new Point(160, 165), 50, 75)));
		figures.add(new ColoredFigureDecorator(new Colour(Color.BLACK),new RectangleBorder(new Point(160, 165), 50, 75)));

		// WINDOW 2
		figures.add(new ColoredFigureDecorator(new Colour(new Color(0, 200, 200)), new Rectangle(new Point(290, 165), 50, 75)));
		figures.add(new ColoredFigureDecorator(new Colour(Color.BLACK),new RectangleBorder(new Point(290, 165), 50, 75)));

		// ROOF
		figures.add(new ColoredFigureDecorator(new Colour(new Color(200, 70, 70)),new Polygon(new Point(100, 100), new Point(225, 30), new Point(350, 100))));
		figures.add(new BrushedFigureDecorator(new Stroke(2), new ColoredFigureDecorator(new Colour(Color.BLACK), new Polyline(new Point(100, 100), new Point(225, 30), new Point(350, 100)))));

		UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		new MainFrame("Рисунок", 550, 350, new Picture(figures));
	}
}
