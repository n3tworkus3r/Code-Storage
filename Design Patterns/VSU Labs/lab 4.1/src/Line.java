import java.awt.Graphics2D;

public class Line  implements MyFigure {
	private Point begin;
	private Point end;

	public Line(Point begin, Point end) {
		this.begin = begin;
		this.end = end;
	}

	public Point getBegin() {
		return begin;
	}

	public Point getEnd() {
		return end;
	}

	public void paint(Graphics2D g) {
		g.drawLine(begin.getX(), begin.getY(), end.getX(), end.getY());
	}
}
