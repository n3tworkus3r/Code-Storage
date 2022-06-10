package view.page;

import controllers.DeleteEquipmentAction;
import controllers.SaveEquipmentAction;
import controllers.ViewEquipmentsAction;
import entity.Equipment;
import view.Page;
import view.Window;
import view.component.Button;
import view.component.Form;
import view.model.EquipmentModelForm;

import java.awt.*;

public class EquipmentPage extends Page {
    public EquipmentPage(Window window, Equipment equipment) {
        super(window);
        Form<Equipment> form = new Form<Equipment>(new EquipmentModelForm(equipment), "Оборудование");
        add(form, BorderLayout.NORTH);
        Panel bottom = new Panel(new FlowLayout(FlowLayout.LEFT, 5, 5));
        bottom.add(new Button("Сохранить", new SaveEquipmentAction(window, form)));
        if(equipment != null) {
            bottom.add(new Button("Удалить", new DeleteEquipmentAction(window, form)));
        }
        bottom.add(new Button("Отменить", new ViewEquipmentsAction(window)));
        add(bottom, BorderLayout.SOUTH);
    }
}
