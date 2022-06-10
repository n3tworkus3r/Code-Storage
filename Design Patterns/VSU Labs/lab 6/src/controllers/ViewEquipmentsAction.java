package controllers;

import entity.Equipment;
import exception.PersistentException;
import service.EquipmentService;
import service.ServiceFactory;
import view.Window;
import view.page.EquipmentsPage;

import java.awt.event.ActionEvent;
import java.util.List;

public class ViewEquipmentsAction extends Action {
    public ViewEquipmentsAction(Window window) {
        super(window);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        try {
            EquipmentService service = ServiceFactory.getService(EquipmentService.class);
            List<Equipment> equipments = service.findAll();
            service.close();
            window.setPage(new EquipmentsPage(window, equipments));
        } catch (PersistentException exception) {
            Window.message("Ошибка", "Невозможно получить список оборудования");
        }
    }
}
