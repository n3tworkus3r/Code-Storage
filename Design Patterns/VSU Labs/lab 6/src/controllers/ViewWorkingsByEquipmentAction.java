package controllers;

import entity.Equipment;
import entity.Working;
import exception.PersistentException;
import service.ServiceFactory;
import service.WorkingService;
import view.Window;
import view.component.Table;
import view.page.WorkingsPage;

import java.awt.event.ActionEvent;
import java.util.List;

public class ViewWorkingsByEquipmentAction extends Action {
    private Table<Equipment> table;

    public ViewWorkingsByEquipmentAction(Window window, Table<Equipment> table) {
        super(window);
        this.table = table;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        Equipment equipment = table.getSelectedEntity();
        if(equipment != null) {
            try {
                WorkingService service = ServiceFactory.getService(WorkingService.class);
                List<Working> workings = service.findByEquipment(equipment);
                service.close();
                window.setPage(new WorkingsPage(window, workings));
            } catch(PersistentException exception) {
                Window.message("Ошибка", "Невозможно прочитать список эксплуатации оборудования");
            }
        }
    }
}
