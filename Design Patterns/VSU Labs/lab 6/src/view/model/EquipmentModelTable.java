package view.model;

import entity.Equipment;
import view.ModelTable;

import java.util.List;

public class EquipmentModelTable extends ModelTable<Equipment> {
    public EquipmentModelTable(List<Equipment> equipments) {
        super(equipments);
    }

    @Override
    public int getColumnCount() {
        return 3;
    }

    @Override
    public String getColumnName(int columnIndex) {
        switch(columnIndex) {
            case 0:
                return "Название";
            case 1:
                return "Цена";
            case 2:
                return "Срок службы";
        }
        return null;
    }

    @Override
    protected String getValue(Equipment author, int index) {
        switch(index) {
            case 0:
                return author.getName();
            case 1:
                return author.getPrice().toString();
            case 2:
                return author.getLifeTime().toString();
        }
        return null;
    }
}
