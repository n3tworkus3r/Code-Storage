package view.page;

import controllers.ViewWorkingAction;
import entity.Working;
import view.Page;
import view.Window;
import view.component.Button;
import view.component.Table;
import view.model.WorkingModelTable;

import java.awt.*;
import java.util.List;

public class WorkingsPage extends Page {
    public WorkingsPage(Window window, List<Working> workings) {
        super(window);
        add(new Label("Список эксплуатации оборудования", Label.CENTER), BorderLayout.NORTH);
        WorkingModelTable model = new WorkingModelTable(workings);
        Table<Working> table = new Table<Working>(model);
        add(table, BorderLayout.CENTER);
        Panel bottom = new Panel(new FlowLayout(FlowLayout.LEFT, 5, 5));
        bottom.add(new view.component.Button("Добавить/редактировать", new ViewWorkingAction(window, table)));
        add(bottom, BorderLayout.SOUTH);
    }
}
