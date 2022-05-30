package by.vsu.model;

import lombok.Data;
import lombok.EqualsAndHashCode;

@Data
@EqualsAndHashCode(callSuper = true)
public class Arc extends Primitive {

    private int x;

    private int y;

    private int width;

    private int height;

    private int startAngle;

    private int arcAngle;

    private String lineColor;

    private String fillColor;

}
