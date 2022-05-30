import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.LinearGradientPaint;
import java.awt.MultipleGradientPaint;

public class LinearGradient implements MyFigure  {
	private MultipleGradientPaint gradient;

	public LinearGradient(Line line, Color beginColor, Color endColor) {
		gradient = new LinearGradientPaint(line.getBegin().getX(), line.getBegin().getY(), line.getEnd().getX(), line.getEnd().getY(), new float[] {0, 1}, new Color[] {beginColor, endColor});
	}

	public void paint(Graphics2D g) {
		g.setPaint(gradient);
	}
}
