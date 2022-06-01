import java.awt.Canvas;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.util.Collection;

public class Picture extends Canvas  {
	private Collection<MyFigure> figures;

	public Picture(Collection<MyFigure> figures) {
		this.figures = figures;
	}

	@Override
	public void paint(Graphics g) {
		super.paint(g);
		Graphics2D g2 = (Graphics2D)g;
		g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		g2.setColor(Color.WHITE);
		java.awt.Rectangle r = getBounds();
		g2.fillRect(r.x, r.y, r.width, r.height);
		for(MyFigure figure : figures)
				figure.paint(g2);
	}
}
