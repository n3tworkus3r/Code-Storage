package window.draw;

public class PainterStorage {
    private static Painter painter = new Painter();

    public static Painter getPainter() {
        return painter;
    }
}
