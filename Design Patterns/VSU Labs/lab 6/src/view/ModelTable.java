package view;

import entity.Entity;

import javax.swing.event.TableModelListener;
import javax.swing.table.TableModel;
import java.util.List;

abstract public class ModelTable<Type extends Entity> implements TableModel {
	private List<Type> entities;

	public ModelTable(List<Type> entities) {
		this.entities = entities;
	}

	@Override
	public Class<?> getColumnClass(int columnIndex) {
		return String.class;
	}

	@Override
	public void addTableModelListener(TableModelListener l) {
	}

	@Override
	public boolean isCellEditable(int rowIndex, int columnIndex) {
		return false;
	}

	@Override
	public void removeTableModelListener(TableModelListener l) {
	}

	@Override
	public void setValueAt(Object aValue, int rowIndex, int columnIndex) {
	}

	@Override
	public int getRowCount() {
		return entities.size();
	}

	abstract protected String getValue(Type entity, int index);

	@Override
	public Object getValueAt(int rowIndex, int columnIndex) {
		return getValue(entities.get(rowIndex), columnIndex);
	}

	public Type getEntity(int index) {
		return entities.get(index);
	}
}
