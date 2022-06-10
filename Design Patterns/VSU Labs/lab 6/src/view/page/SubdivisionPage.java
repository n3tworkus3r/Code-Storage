package view.page;

import controllers.*;
import entity.Subdivision;
import view.Page;
import view.Window;
import view.component.Button;
import view.component.Form;
import view.model.SubdivisionModelForm;

import java.awt.*;
import java.util.List;

public class SubdivisionPage extends Page {
    public SubdivisionPage(Window window, Subdivision subdivision) {
        super(window);
        Form<Subdivision> form = new Form<Subdivision>(new SubdivisionModelForm(subdivision), "Подразделение");
        add(form, BorderLayout.NORTH);
        Panel bottom = new Panel(new FlowLayout(FlowLayout.LEFT, 5, 5));
        bottom.add(new Button("Сохранить", new SaveSubdivisionAction(window, form)));
        if(subdivision != null) {
            bottom.add(new Button("Удалить", new DeleteSubdivisionAction(window, form)));
        }
        bottom.add(new Button("Отменить", new ViewSubdivisionsAction(window)));
        add(bottom, BorderLayout.SOUTH);
    }
}
