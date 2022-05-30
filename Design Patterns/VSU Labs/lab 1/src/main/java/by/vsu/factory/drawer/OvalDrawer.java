package by.vsu.factory.drawer;

import by.vsu.model.Oval;
import by.vsu.model.Primitive;

import java.awt.Color;
import java.awt.Graphics;

public class OvalDrawer implements PrimitiveDrawer {

    @Override
    public void drawPrimitive(Primitive primitive, Graphics graphics) {
        Oval oval = (Oval) primitive;

        int x = oval.getX();
        int y = oval.getY();
        int width = oval.getWidth();
        int height = oval.getHeight();
        Color fillColor = Color.decode(oval.getFillColor());
        Color lineColor = Color.decode(oval.getLineColor());

        graphics.setColor(fillColor);
        graphics.fillOval(x, y, width, height);
        graphics.setColor(lineColor);
        graphics.drawOval(x, y, width, height);
    }

}
