package view.model;

import entity.Subdivision;
import view.ModelTable;

import java.util.List;

public class SubdivisionModelTable extends ModelTable<Subdivision> {
    public SubdivisionModelTable(List<Subdivision> subdivisions) {
        super(subdivisions);
    }

    @Override
    public int getColumnCount() {
        return 1;
    }

    @Override
    public String getColumnName(int columnIndex) {
        switch(columnIndex) {
            case 0:
                return "Название";
        }
        return null;
    }

    @Override
    protected String getValue(Subdivision author, int index) {
        switch(index) {
            case 0:
                return author.getName();
        }
        return null;
    }
}
