package by.vsu.reader;

import by.vsu.config.ObjectMapperConfig;
import by.vsu.model.Primitive;
import by.vsu.util.PrimitiveConverter;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class JsonPrimitiveReader implements PrimitiveReader {

    private final ObjectMapper mapper;

    public JsonPrimitiveReader() {
        mapper = ObjectMapperConfig.getMapper();
    }

    @Override
    public Primitive read(String filename) throws IOException {
        File file = new File(filename);

        return read(file);
    }

    @Override
    public Primitive read(File file) throws IOException {
        JsonNode jsonNode = mapper.readTree(file);

        return readObject(jsonNode);
    }

    @Override
    public List<Primitive> readAll(String filename) throws IOException {
        File file = new File(filename);

        return readAll(file);
    }

    @Override
    public List<Primitive> readAll(File file) throws IOException {
        List<Primitive> objects = new ArrayList<>();
        JsonNode jsonNodes = mapper.readTree(file);

        for (JsonNode jsonNode : jsonNodes) {
            objects.add(readObject(jsonNode));
        }

        return objects;
    }

    private Primitive readObject(JsonNode primitiveJson) throws IOException {
        String type = primitiveJson.get("type").asText();

        try {
            return (Primitive) mapper.readValue(primitiveJson.toString(), PrimitiveConverter.getClassByType(type));
        } catch (ClassNotFoundException e) {
            throw new IOException(e);
        }
    }

}
