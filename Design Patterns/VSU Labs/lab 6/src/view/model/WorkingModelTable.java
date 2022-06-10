package view.model;

import entity.Working;
import view.ModelTable;

import java.text.DateFormat;
import java.util.List;
import java.util.Locale;

public class WorkingModelTable extends ModelTable<Working> {
    public WorkingModelTable(List<Working> workings) {
        super(workings);
    }

    @Override
    public int getColumnCount() {
        return 3;
    }

    @Override
    public String getColumnName(int columnIndex) {
        switch(columnIndex) {
            case 0:
                return "Оборудование";
            case 1:
                return "Подразделение";
            case 2:
                return "Дата ввода в эксплуатацию";
        }
        return null;
    }

    @Override
    protected String getValue(Working working, int index) {
        DateFormat format = DateFormat.getDateInstance(DateFormat.MEDIUM, Locale.GERMANY);

        switch(index) {
            case 0:
                return working.getEquipment().getName();
            case 1:
                return working.getSubdivision().getName();
            case 2:
                return format.format(working.getDateOfInput());
        }
        return null;
    }
}
