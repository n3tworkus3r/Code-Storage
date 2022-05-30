package by.vsu.factory.drawer;

import by.vsu.model.Polygon;
import by.vsu.model.Primitive;

import java.awt.Color;
import java.awt.Graphics;

public class PolygonDrawer implements PrimitiveDrawer {

    @Override
    public void drawPrimitive(Primitive primitive, Graphics graphics) {
        Polygon polygon = (Polygon) primitive;

        if (polygon.getX().length != polygon.getY().length) {
            throw new RuntimeException("Polygon's count of x values is not equal to count of y values.");
        }

        Color fillColor = Color.decode(polygon.getFillColor());
        Color lineColor = Color.decode(polygon.getLineColor());

        graphics.setColor(fillColor);
        graphics.fillPolygon(polygon.getX(), polygon.getY(), polygon.getX().length);
        graphics.setColor(lineColor);
        graphics.drawPolygon(polygon.getX(), polygon.getY(), polygon.getX().length);
    }

}
