package controllers;

import entity.Equipment;
import entity.Subdivision;
import entity.Working;
import exception.PersistentException;
import service.EquipmentService;
import service.ServiceFactory;
import service.SubdivisionService;
import view.Window;
import view.component.Table;
import view.page.WorkingPage;

import java.awt.event.ActionEvent;
import java.util.List;

public class ViewWorkingAction extends Action {
    private Table<Working> table;

    public ViewWorkingAction(Window window, Table<Working> table) {
        super(window);
        this.table = table;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        try {
            EquipmentService service = ServiceFactory.getService(EquipmentService.class);
            List<Equipment> equipments = service.findAll();
            service.close();
            SubdivisionService service1 = ServiceFactory.getService(SubdivisionService.class);
            List<Subdivision> subdivisions = service1.findAll();
            service1.close();
            window.setPage(new WorkingPage(window, table.getSelectedEntity(), equipments, subdivisions));
        } catch(PersistentException exception) {
            Window.message("Ошибка", "Невозможно прочитать список оборудования или подразделений");
        }
    }
}
