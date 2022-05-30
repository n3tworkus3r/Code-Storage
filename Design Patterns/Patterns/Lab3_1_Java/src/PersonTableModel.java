import java.text.DateFormat;
import java.util.ArrayList;
import java.util.List;

import javax.swing.event.TableModelEvent;
import javax.swing.event.TableModelListener;
import javax.swing.table.TableModel;

public class PersonTableModel implements TableModel {
    private List<Person> persons;
    private DateFormat format;

    public PersonTableModel(List<Person> persons) {
        this.persons = persons;
        format = DateFormat.getDateInstance(DateFormat.MEDIUM);
    }

    @Override
    public int getColumnCount() {
        return 5;
    }

    @Override
    public String getColumnName(int index) {
        switch(index) {
            case 0: return "Фамилия";
            case 1: return "Имя";
            case 2: return "Отчество";
            case 3: return "Дата рождения";
            case 4: return "Почтовый адрес";
        }
        return null;
    }

    @Override
    public Class<?> getColumnClass(int index) {
        return String.class;
    }

    @Override
    public int getRowCount() {
        return persons.size();
    }

    @Override
    public Object getValueAt(int rowIndex, int colIndex) {
        switch(colIndex) {
            case 0: return persons.get(rowIndex).getLastName();
            case 1: return persons.get(rowIndex).getFirstName();
            case 2: return persons.get(rowIndex).getMiddleName();
            case 3:
                if(persons.get(rowIndex).getBirthday() != null) {
                    return format.format(
                        persons.get(rowIndex).getBirthday()
                    );
                } else {
                    return "неизвестна";
                }
            case 4: return persons.get(rowIndex).getPostAddress();
        }
        return null;
    }

    @Override
    public void setValueAt(Object value, int rowIndex, int colIndex) {}

    @Override
    public boolean isCellEditable(int rowIndex, int colIndex) {
        return false;
    }

    private List<TableModelListener> listeners = new ArrayList<>();

    @Override
    public void addTableModelListener(TableModelListener listener) {
        listeners.add(listener);
    }

    @Override
    public void removeTableModelListener(TableModelListener listener) {
        listeners.remove(listener);
    }

    public List<Person> getPersons() {
        return persons;
    }

    public void update() {
        for(TableModelListener listener : listeners) {
            listener.tableChanged(new TableModelEvent(this));
        }
    }
}