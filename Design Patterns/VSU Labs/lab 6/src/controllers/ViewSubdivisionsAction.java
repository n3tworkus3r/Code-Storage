package controllers;

import entity.Equipment;
import entity.Subdivision;
import exception.PersistentException;
import service.EquipmentService;
import service.ServiceFactory;
import service.SubdivisionService;
import view.Window;
import view.component.Table;
import view.page.SubdivisionsPage;

import java.awt.event.ActionEvent;
import java.util.List;

public class ViewSubdivisionsAction extends Action {
    public ViewSubdivisionsAction(Window window) {
        super(window);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        try {
            SubdivisionService service = ServiceFactory.getService(SubdivisionService.class);
            List<Subdivision> subdivisions = service.findAll();
            service.close();
            window.setPage(new SubdivisionsPage(window, subdivisions));
        } catch (PersistentException exception) {
            Window.message("Ошибка", "Невозможно получить список подразделений");
        }
    }
}
