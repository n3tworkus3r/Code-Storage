package controllers;

import entity.Equipment;
import exception.IntegrityViolationException;
import exception.PersistentException;
import service.EquipmentService;
import service.ServiceFactory;
import view.Window;
import view.component.Form;
import view.page.EquipmentPage;

import java.awt.event.ActionEvent;

public class DeleteEquipmentAction extends Action  {
    private Form<Equipment> form;

    public DeleteEquipmentAction(Window window, Form<Equipment> form) {
        super(window);
        this.form = form;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        Equipment equipment = form.getEntity();
        if(equipment != null) {
            try {
                EquipmentService service = ServiceFactory.getService(EquipmentService.class);
                service.delete(equipment.getIdentity());
                service.close();
                window.setPage(new EquipmentPage(window, null));
                Window.message("Сообщение", "Оборудование успешно удалёно");
            } catch(IntegrityViolationException exception) {
                Window.message("Ошибка", "Невозможно удалить оборудование из-за его эксплуатации");
            } catch(PersistentException exception) {
                Window.message("Ошибка", "Невозможно удалить оборудование");
            }
        }
    }
}
