import java.awt.Graphics2D;

public class Point implements MyFigure{
	private int x;
	private int y;

	public Point(int x, int y) {
		this.x = x;
		this.y = y;
	}

	public int getX() {
		return x;
	}

	public int getY() {
		return y;
	}

	public void paint(Graphics2D g) {
		g.fillOval(x - 1, y - 1, 2, 2);
	}
}
