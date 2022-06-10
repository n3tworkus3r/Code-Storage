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

public class SaveWorkingAction extends Action {
    private Form<Working> form;

    public SaveWorkingAction(Window window, Form<Working> form) {
        super(window);
        this.form = form;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        Working working = form.getEntity();
        if(working != null) {
            try {
                WorkingService workingService = ServiceFactory.getService(WorkingService.class);
                workingService.save(working);
                workingService.close();
                Window.message("Сообщение", "Эксплуатация успешно сохранена");
                try {
                    EquipmentService equipmentService = ServiceFactory.getService(EquipmentService.class);
                    List<Equipment> equipments = equipmentService.findAll();
                    equipmentService.close();
                    SubdivisionService subdivisionService = ServiceFactory.getService(SubdivisionService.class);
                    List<Subdivision> subdivisions = subdivisionService.findAll();
                    equipmentService.close();
                    window.setPage(new WorkingPage(window, working, equipments, subdivisions));
                } catch(PersistentException exception) {
                    Window.message("Ошибка", "Невозможно получить список оборудования или подразделений");
                }
            } catch(PersistentException exception) {
                Window.message("Ошибка", "Невозможно сохранить эксплуатацию");
            }
        }
    }
}
