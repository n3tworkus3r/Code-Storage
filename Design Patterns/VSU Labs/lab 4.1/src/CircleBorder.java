import java.awt.Graphics2D;

public class CircleBorder implements MyFigure  {
	private int x;
	private int y;
	private int diameter;

	public CircleBorder(Point center, int radius) {
		x = center.getX() - radius;
		y = center.getY() - radius;
		diameter = 2 * radius;
	}

	public void paint(Graphics2D g) {
		g.drawOval(x, y, diameter, diameter);
	}
}
