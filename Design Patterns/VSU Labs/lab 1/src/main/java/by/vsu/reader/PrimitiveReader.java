package by.vsu.reader;

import by.vsu.model.Primitive;

import java.io.File;
import java.io.IOException;
import java.util.List;

public interface PrimitiveReader {

    Primitive read(String filename) throws IOException;

    Primitive read(File file) throws IOException;

    List<Primitive> readAll(String filename) throws IOException;

    List<Primitive> readAll(File file) throws IOException;

}
