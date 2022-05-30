package by.vsu.factory.reader;

import by.vsu.exception.UnsupportedExtensionException;
import by.vsu.reader.Format;
import by.vsu.reader.JsonPrimitiveReader;
import by.vsu.reader.PrimitiveReader;

public class ReaderFactory {

    private ReaderFactory() {
    }

    public static PrimitiveReader getReader(String extension) {
        if (Format.JSON.name().equalsIgnoreCase(extension)) {
            return new JsonPrimitiveReader();
        } else {
            throw new UnsupportedExtensionException(String.format("Given extension is not supported: %s", extension));
        }
    }

}
