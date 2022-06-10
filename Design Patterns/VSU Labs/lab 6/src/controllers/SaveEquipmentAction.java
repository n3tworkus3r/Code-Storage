package controllers;

import entity.Equipment;
import exception.PersistentException;
import service.EquipmentService;
import service.ServiceFactory;
import view.Window;
import view.component.Form;
import view.page.EquipmentPage;

import java.awt.event.ActionEvent;

public class SaveEquipmentAction extends Action {
    private Form<Equipment> form;

    public SaveEquipmentAction(Window window, Form<Equipment> form) {
        super(window);
        this.form = form;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        Equipment equipment = form.getEntity();
        if(equipment != null) {
            try {
                EquipmentService service = ServiceFactory.getService(EquipmentService.class);
                service.save(equipment);
                service.close();
                window.setPage(new EquipmentPage(window, equipment));
                Window.message("Сообщение", "Оборудование успешно сохранёно");
            } catch(PersistentException exception) {
                Window.message("Ошибка", "Невозможно сохранить оборудование");
            }
        }
    }
}
