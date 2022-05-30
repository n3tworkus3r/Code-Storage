package by.vsu.factory.drawer;

import by.vsu.model.Primitive;
import by.vsu.model.Rectangle;

import java.awt.Color;
import java.awt.Graphics;

public class RectangleDrawer implements PrimitiveDrawer {

    @Override
    public void drawPrimitive(Primitive primitive, Graphics graphics) {
        Rectangle rectangle = (Rectangle) primitive;

        int x = rectangle.getX();
        int y = rectangle.getY();
        int width = rectangle.getWidth();
        int height = rectangle.getHeight();
        Color fillColor = Color.decode(rectangle.getFillColor());
        Color lineColor = Color.decode(rectangle.getLineColor());

        graphics.setColor(fillColor);
        graphics.fillRect(x, y, width, height);
        graphics.setColor(lineColor);
        graphics.drawRect(x, y, width, height);
    }

}
