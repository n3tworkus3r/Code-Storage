package by.vsu.service;

import by.vsu.model.wrapper.PrimitiveWrapper;
import by.vsu.reader.PrimitiveReader;

import java.io.IOException;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

public class PrimitiveService {

    public List<PrimitiveWrapper> getPrimitives(String filename, PrimitiveReader primitiveReader) throws IOException {
        return primitiveReader.readAll(filename)
                .stream()
                .map(primitive -> PrimitiveWrapper.builder()
                        .type(primitive.getType())
                        .primitive(primitive)
                        .build())
                .sorted(Comparator.comparingInt(wrapper -> wrapper.getPrimitive().getLayer()))
                .collect(Collectors.toList());
    }

}
