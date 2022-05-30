package by.vsu.factory.drawer;

import by.vsu.model.Line;
import by.vsu.model.Primitive;

import java.awt.Color;
import java.awt.Graphics;

public class LineDrawer implements PrimitiveDrawer {

    @Override
    public void drawPrimitive(Primitive primitive, Graphics graphics) {
        Line line = (Line) primitive;

        int x1 = line.getX1();
        int x2 = line.getX2();
        int y1 = line.getY1();
        int y2 = line.getY2();
        Color lineColor = Color.decode(line.getLineColor());

        graphics.setColor(lineColor);
        graphics.drawLine(x1, y1, x2, y2);
    }

}
