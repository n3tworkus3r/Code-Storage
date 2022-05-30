package by.vsu.factory.drawer;

import by.vsu.model.Arc;
import by.vsu.model.Primitive;

import java.awt.Color;
import java.awt.Graphics;

public class ArcDrawer implements PrimitiveDrawer {

    @Override
    public void drawPrimitive(Primitive primitive, Graphics graphics) {
        Arc arc = (Arc) primitive;

        int x = arc.getX();
        int y = arc.getY();
        int width = arc.getWidth();
        int height = arc.getHeight();
        int startAngle = arc.getStartAngle();
        int angle = arc.getArcAngle();
        Color lineColor = Color.decode(arc.getLineColor());
        Color fillColor = Color.decode(arc.getFillColor());

        graphics.setColor(lineColor);
        graphics.fillArc(x, y, width, height, startAngle, angle);
        graphics.setColor(fillColor);
        graphics.drawArc(x, y, width, height, startAngle, angle);
    }

}
