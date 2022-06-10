package view.page;

import controllers.DeleteWorkingAction;
import controllers.SaveWorkingAction;
import controllers.ViewWorkingsAction;
import entity.Equipment;
import entity.Subdivision;
import entity.Working;
import view.Page;
import view.Window;
import view.component.Button;
import view.component.Form;
import view.model.WorkingModelForm;

import java.awt.*;
import java.util.List;

public class WorkingPage extends Page {
    public WorkingPage(Window window, Working working, List<Equipment> equipments, List<Subdivision> subdivisions) {
        super(window);
        Form<Working> form = new Form<Working>(new WorkingModelForm(working, equipments, subdivisions), "Эксплуатация оборудования");
        add(form, BorderLayout.NORTH);
        Panel bottom = new Panel(new FlowLayout(FlowLayout.LEFT, 5, 5));
        bottom.add(new view.component.Button("Сохранить", new SaveWorkingAction(window, form)));
        if(working != null) {
            bottom.add(new view.component.Button("Удалить", new DeleteWorkingAction(window, form)));
        }
        bottom.add(new Button("Отменить", new ViewWorkingsAction(window)));
        add(bottom, BorderLayout.SOUTH);
    }
}
