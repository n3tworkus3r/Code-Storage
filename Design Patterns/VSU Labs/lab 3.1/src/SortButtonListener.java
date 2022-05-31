import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Collections;

import javax.swing.JComboBox;

public class SortButtonListener implements ActionListener {
    private JComboBox<String> comboBox;
    private PersonTableModel model;

    public SortButtonListener(JComboBox<String> comboBox, PersonTableModel model) {
        this.comboBox = comboBox;
        this.model = model;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        java.util.Comparator<Person> comparator = new PersonDateComparator();
        if (comboBox.getSelectedItem()!=comparator.toString()) {
            comparator =new PersonDoWComparator();
            if (comboBox.getSelectedItem()!=comparator.toString())
                comparator =new PersonMonthComparator();
        }
        Collections.sort(model.getPersons(), comparator);
        model.update();
    }
}
