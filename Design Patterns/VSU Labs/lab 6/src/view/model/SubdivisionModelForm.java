package view.model;

import entity.Subdivision;
import view.ModelForm;
import view.Window;

import java.awt.*;
import java.util.LinkedHashMap;

public class SubdivisionModelForm extends ModelForm<Subdivision> {
    public SubdivisionModelForm(Subdivision entity) {
        super(entity);
    }

    @Override
    protected LinkedHashMap<String, Component> createFields(Subdivision subdivision) {
        LinkedHashMap<String, Component> map = new LinkedHashMap<String, Component>();
        TextField nameField = new TextField();

        if(subdivision != null) {
            nameField.setText(subdivision.getName());

        }
        map.put("Название подразделения", nameField);

        return map;
    }

    @Override
    protected Subdivision createEntity(LinkedHashMap<String, Component> fields) {
        Subdivision subdivision = new Subdivision();
        subdivision.setName(((TextField)fields.get("Название подразделения")).getText());
        return subdivision;
    }
}
