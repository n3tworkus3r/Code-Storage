package view.component;

import entity.Entity;
import view.ModelTable;
import javax.swing.table.TableModel;
import javax.swing.table.TableRowSorter;

import javax.swing.*;

public class Table<Type extends Entity> extends JScrollPane {
	private ModelTable<Type> model;
	private JTable tableContent;

	public Table(ModelTable<Type> model) {
		this.model = model;

		tableContent = new JTable(model);
		TableRowSorter<TableModel> sorter = new TableRowSorter<>(tableContent.getModel());
		tableContent.setRowSorter(sorter);

		tableContent.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		setViewportView(tableContent);

	}


	public Type getSelectedEntity() {
		int index = tableContent.getSelectedRow();
		if(index != -1) {
			return model.getEntity(index);
		}
		return null;
	}
}
