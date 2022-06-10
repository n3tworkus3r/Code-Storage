package controllers;

import entity.Equipment;
import entity.Subdivision;
import entity.Working;
import exception.PersistentException;
import service.EquipmentService;
import service.ServiceFactory;
import service.SubdivisionService;
import service.WorkingService;
import view.Window;
import view.component.Form;
import view.page.WorkingPage;

import java.awt.event.ActionEvent;
import java.util.List;

public class DeleteWorkingAction extends Action {
    private Form<Working> form;

    public DeleteWorkingAction(Window window, Form<Working> form) {
        super(window);
        this.form = form;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        Working working = form.getEntity();
        if(working != null) {
            try {
                WorkingService workingService = ServiceFactory.getService(WorkingService.class);
                workingService.delete(working.getIdentity());
                workingService.close();
                Window.message("Сообщение", "Эксплуатация успешно удалена");
                try {
                    EquipmentService equipmentService = ServiceFactory.getService(EquipmentService.class);
                    List<Equipment> equipments = equipmentService.findAll();
                    equipmentService.close();
                    SubdivisionService subdivisionService = ServiceFactory.getService(SubdivisionService.class);
                    List<Subdivision> subdivisions = subdivisionService.findAll();
                    equipmentService.close();
                    window.setPage(new WorkingPage(window, null, equipments, subdivisions));
                } catch(PersistentException exception) {
                    Window.message("Ошибка", "Невозможно получить список оборудования или подразделений");
                }
            } catch(PersistentException exception) {
                Window.message("Ошибка", "Невозможно удалить эксплуатацаю");
            }
        }
    }
}
