import java.awt.BasicStroke;
import java.awt.Graphics2D;

public class Stroke implements MyFigure{
	private java.awt.Stroke stroke;

	public Stroke(int width) {
		stroke = new BasicStroke((float)width);
	}

	public void paint(Graphics2D g) {
		g.setStroke(stroke);
	}
}
