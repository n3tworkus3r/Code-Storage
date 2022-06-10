package controllers;

import entity.Equipment;
import view.Window;
import view.component.Table;
import view.page.EquipmentPage;

import java.awt.event.ActionEvent;

public class ViewEquipmentAction extends Action {
    private Table<Equipment> table;

    public ViewEquipmentAction(Window window, Table<Equipment> table) {
        super(window);
        this.table = table;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        window.setPage(new EquipmentPage(window, table.getSelectedEntity()));
    }
}
