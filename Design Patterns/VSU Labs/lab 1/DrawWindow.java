package by.vsu;

import by.vsu.exception.DrawingException;
import by.vsu.factory.reader.ReaderFactory;
import by.vsu.model.wrapper.PrimitiveWrapper;
import by.vsu.reader.PrimitiveReader;
import by.vsu.service.PrimitiveService;
import by.vsu.util.PrimitiveConverter;
import org.apache.commons.io.FilenameUtils;

import javax.swing.JFrame;
import java.awt.Graphics;

public class DrawWindow extends JFrame {

    private final String filename;

    private final PrimitiveService primitiveService;

    public DrawWindow(String filename) {
        super("Primitive drawer");
        setSize(1280, 720);
        setVisible(true);

        this.primitiveService = new PrimitiveService();
        this.filename = filename;
    }

    public void paint(Graphics graphics) {
        super.paint(graphics);

        try {
            PrimitiveReader primitiveReader = ReaderFactory.getReader(FilenameUtils.getExtension(filename));

            for (PrimitiveWrapper primitiveWrapper : primitiveService.getPrimitives(filename, primitiveReader)) {
                PrimitiveConverter
                        .getFactoryByType(primitiveWrapper.getType())
                        .drawPrimitive(primitiveWrapper.getPrimitive(), graphics);
            }
        } catch (Exception e) {
            throw new DrawingException(e);
        }
    }

}
