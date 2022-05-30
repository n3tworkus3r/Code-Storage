package by.vsu.model.wrapper;

import by.vsu.model.Primitive;
import lombok.AccessLevel;
import lombok.Builder;
import lombok.Data;
import lombok.Setter;

@Data
@Builder
public class PrimitiveWrapper {

    @Setter(AccessLevel.NONE)
    private String type;

    @Setter(AccessLevel.NONE)
    private Primitive primitive;

}
