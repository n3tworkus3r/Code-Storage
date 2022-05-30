package by.vsu.model;

import lombok.Data;
import lombok.EqualsAndHashCode;

@Data
@EqualsAndHashCode(callSuper = true)
public class Polygon extends Primitive {

    private int[] x;

    private int[] y;

    private String lineColor;

    private String fillColor;

}
