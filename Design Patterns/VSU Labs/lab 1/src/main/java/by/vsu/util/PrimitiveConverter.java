package by.vsu.util;

import by.vsu.factory.drawer.ArcDrawer;
import by.vsu.factory.drawer.LineDrawer;
import by.vsu.factory.drawer.OvalDrawer;
import by.vsu.factory.drawer.PolygonDrawer;
import by.vsu.factory.drawer.PrimitiveDrawer;
import by.vsu.factory.drawer.RectangleDrawer;
import by.vsu.model.Arc;
import by.vsu.model.Line;
import by.vsu.model.Oval;
import by.vsu.model.Polygon;
import by.vsu.model.PrimitiveType;
import by.vsu.model.Rectangle;

import java.util.HashMap;
import java.util.Locale;
import java.util.Map;

public class PrimitiveConverter {

    private static final Map<PrimitiveType, Class<?>> TYPE_TO_CLASS = new HashMap<>();
    private static final Map<PrimitiveType, PrimitiveDrawer> TYPE_TO_FACTORY = new HashMap<>();

    static {
        putPrimitiveMeta(PrimitiveType.ARC, Arc.class, new ArcDrawer());
        putPrimitiveMeta(PrimitiveType.LINE, Line.class, new LineDrawer());
        putPrimitiveMeta(PrimitiveType.OVAL, Oval.class, new OvalDrawer());
        putPrimitiveMeta(PrimitiveType.POLYGON, Polygon.class, new PolygonDrawer());
        putPrimitiveMeta(PrimitiveType.RECTANGLE, Rectangle.class, new RectangleDrawer());
    }

    private PrimitiveConverter() {
    }

    public static Class<?> getClassByType(String type) throws ClassNotFoundException {
        PrimitiveType primitiveType = PrimitiveType.valueOf(type.toUpperCase(Locale.ROOT));

        if (TYPE_TO_CLASS.containsKey(primitiveType)) {
            return TYPE_TO_CLASS.get(primitiveType);
        } else {
            throw new ClassNotFoundException(String.format("Class isn't found with given primitive type: %s", type));
        }
    }

    public static PrimitiveDrawer getFactoryByType(String type) throws RuntimeException {
        PrimitiveType primitiveType = PrimitiveType.valueOf(type.toUpperCase(Locale.ROOT));

        if (TYPE_TO_CLASS.containsKey(primitiveType)) {
            return TYPE_TO_FACTORY.get(primitiveType);
        } else {
            throw new RuntimeException(String.format("Factory isn't found with given primitive type: %s", type));
        }
    }

    private static void putPrimitiveMeta(PrimitiveType typeName, Class<?> className, PrimitiveDrawer primitiveDrawer) {
        TYPE_TO_CLASS.put(typeName, className);
        TYPE_TO_FACTORY.put(typeName, primitiveDrawer);
    }

}
