package view.page;

import controllers.ViewSubdivisionAction;
import controllers.ViewWorkingsBySubdivisionAction;
import entity.Subdivision;
import view.Page;
import view.Window;
import view.component.Button;
import view.component.Table;
import view.model.SubdivisionModelTable;

import java.awt.*;
import java.util.List;

public class SubdivisionsPage extends Page {
    public SubdivisionsPage(Window window, List<Subdivision> subdivisions) {
        super(window);
        add(new Label("Список подразделений", Label.CENTER), BorderLayout.NORTH);
        SubdivisionModelTable model = new SubdivisionModelTable(subdivisions);
        Table<Subdivision> table = new Table<Subdivision>(model);
        add(table, BorderLayout.CENTER);
        Panel bottom = new Panel(new FlowLayout(FlowLayout.LEFT, 5, 5));
        bottom.add(new view.component.Button("Добавить/редактировать", new ViewSubdivisionAction(window, table)));
        bottom.add(new Button("Список эксплуатации", new ViewWorkingsBySubdivisionAction(window, table)));
        add(bottom, BorderLayout.SOUTH);
    }
}
