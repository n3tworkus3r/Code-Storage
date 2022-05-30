import java.awt.Color;
import java.awt.Graphics2D;

public class Colour {
	private Color color;

	public Colour(Color color) {
		this.color = color;
	}

	public void paint(Graphics2D g) {
		g.setColor(color);
	}
}
