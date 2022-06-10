package view.model;

import entity.Equipment;
import view.ModelForm;
import view.Window;

import java.awt.*;
import java.util.LinkedHashMap;

public class EquipmentModelForm extends ModelForm<Equipment> {
    public EquipmentModelForm(Equipment entity) {
        super(entity);
    }

    @Override
    protected LinkedHashMap<String, Component> createFields(Equipment equipment) {
        LinkedHashMap<String, Component> map = new LinkedHashMap<String, Component>();
        TextField nameField = new TextField();
        TextField priceField = new TextField();
        TextField lifeTimeField = new TextField();
        if(equipment != null) {
            nameField.setText(equipment.getName());
            priceField.setText(equipment.getPrice().toString());
            lifeTimeField.setText(equipment.getLifeTime().toString());
        }
        map.put("Название обрудования", nameField);
        map.put("Цена", priceField);
        map.put("Срок службы(в днях)", lifeTimeField);
        return map;
    }

    @Override
    protected Equipment createEntity(LinkedHashMap<String, Component> fields) {
        Equipment equipment = new Equipment();
        equipment.setName(((TextField)fields.get("Название обрудования")).getText());
        try {
            equipment.setPrice(Double.parseDouble(((TextField)fields.get("Цена")).getText()));
        } catch(NumberFormatException e) {
            view.Window.message("Ошибка", "Цена должена быть числом");
            return null;
        }
        try {
            equipment.setLifeTime(Integer.parseInt(((TextField)fields.get("Срок службы(в днях)")).getText()));
        } catch(NumberFormatException e) {
            Window.message("Ошибка", "Срок службы должен быть числом");
            return null;
        }
        return equipment;
    }
}
