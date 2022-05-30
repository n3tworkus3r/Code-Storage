package by.vsu.model;

import lombok.Data;
import lombok.EqualsAndHashCode;

@Data
@EqualsAndHashCode(callSuper = true)
public class Line extends Primitive {

    private int x1;

    private int y1;

    private int x2;

    private int y2;

    private String lineColor;

}
