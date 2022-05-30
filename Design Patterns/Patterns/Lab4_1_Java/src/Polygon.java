import java.awt.Graphics2D;

public class Polygon implements MyFigure{
	private int[] x;
	private int[] y;
	private int n;

	public Polygon(Point ... points) {
		n = points.length;
		x = new int[n];
		y = new int[n];
		for(int i = 0; i < n; i++) {
			x[i] = points[i].getX();
			y[i] = points[i].getY();
		}
	}

	public void paint(Graphics2D g) {
		g.fillPolygon(x, y, n);
	}
}
