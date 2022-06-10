package controllers;

import entity.Equipment;
import entity.Subdivision;
import view.Window;
import view.component.Table;
import view.page.SubdivisionPage;

import java.awt.event.ActionEvent;

public class ViewSubdivisionAction extends Action {
    private Table<Subdivision> table;

    public ViewSubdivisionAction(Window window, Table<Subdivision> table) {
        super(window);
        this.table = table;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        window.setPage(new SubdivisionPage(window, table.getSelectedEntity()));
    }
}
