package by.vsu.model;

import lombok.Data;
import lombok.EqualsAndHashCode;

@Data
@EqualsAndHashCode(callSuper = true)
public class Rectangle extends Primitive {

    private int x;

    private int y;

    private int width;

    private int height;

    private String lineColor;

    private String fillColor;

}
