package view.model;

import entity.Equipment;
import entity.Subdivision;
import entity.Working;
import view.ModelForm;
import view.Window;

import java.awt.*;
import java.text.DateFormat;
import java.text.ParseException;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Locale;

public class WorkingModelForm extends ModelForm<Working> {
    private List<Equipment> equipments;
    List<Subdivision> subdivisions;
    private Choice equipmentField;
    private Choice subdivisionField;

    public WorkingModelForm(Working working, List<Equipment> equipments, List<Subdivision> subdivisions) {
        super(working);
        this.equipments = equipments;
        this.subdivisions = subdivisions;
        for(Equipment equipment : equipments) {
            equipmentField.add(equipment.getName());
        }
        for(Subdivision subdivision : subdivisions) {
            subdivisionField.add(subdivision.getName());
            System.out.println(3);
        }
        if(working != null) {
            equipmentField.select(equipments.indexOf(working.getEquipment()));
            subdivisionField.select(subdivisions.indexOf(working.getSubdivision()));
        }
    }

    @Override
    protected LinkedHashMap<String, Component> createFields(Working working) {
        DateFormat format = DateFormat.getDateInstance(DateFormat.MEDIUM, Locale.GERMANY);
        LinkedHashMap<String, Component> map = new LinkedHashMap<String, Component>();
        equipmentField = new Choice();
        subdivisionField = new Choice();
        TextField dateOfInput = new TextField();
        if(working != null) {
            dateOfInput.setText(format.format(working.getDateOfInput()));
        }
        map.put("Оборудувание", equipmentField);
        map.put("Подразделение", subdivisionField);
        map.put("Дата ввода в экплуатацию(Пример: 20.03.2000)", dateOfInput);
        return map;
    }

    @Override
    protected Working createEntity(LinkedHashMap<String, Component> fields) {
        DateFormat format = DateFormat.getDateInstance(DateFormat.MEDIUM);
        Working working = new Working();
        if(((Choice)fields.get("Оборудувание")).getItemCount() == 0){
            Window.message("Ошибка", "Нет никакого оборудования");
            return null;
        }
        working.setEquipment(equipments.get(((Choice)fields.get("Оборудувание")).getSelectedIndex()));
        if(((Choice)fields.get("Подразделение")).getItemCount() == 0){
            Window.message("Ошибка", "Нет никаких подразделений");
            return null;
        }
        working.setSubdivision(subdivisions.get(((Choice)fields.get("Подразделение")).getSelectedIndex()));
        try {
            working.setDateOfInput(format.parse(((TextField)fields.get("Дата ввода в экплуатацию(Пример: 20.03.2000)")).getText()));
        } catch(ParseException e) {
            Window.message("Ошибка", "Дата ввода в экплуатацию долна быть введена в формате -> ДД.ММ.ГГГГ");
            return null;
        }
        return working;
    }
}
