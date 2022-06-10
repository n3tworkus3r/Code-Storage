package view.page;

import controllers.ViewEquipmentAction;
import controllers.ViewWorkingsByEquipmentAction;
import entity.Equipment;
import view.Page;
import view.Window;
import view.component.Button;
import view.component.Table;
import view.model.EquipmentModelTable;

import java.awt.*;
import java.util.List;

public class EquipmentsPage extends Page {
    public EquipmentsPage(Window window, List<Equipment> equipments) {
        super(window);
        add(new Label("Список оборудования", Label.CENTER), BorderLayout.NORTH);
        EquipmentModelTable model = new EquipmentModelTable(equipments);
        Table<Equipment> table = new Table<Equipment>(model);
        add(table, BorderLayout.CENTER);
        Panel bottom = new Panel(new FlowLayout(FlowLayout.LEFT, 5, 5));
        bottom.add(new view.component.Button("Добавить/редактировать", new ViewEquipmentAction(window, table)));
        bottom.add(new Button("Список эксплуатации", new ViewWorkingsByEquipmentAction(window, table)));
        add(bottom, BorderLayout.SOUTH);
    }
}
