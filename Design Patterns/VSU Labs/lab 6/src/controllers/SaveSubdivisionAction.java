package controllers;

import entity.Subdivision;
import exception.PersistentException;
import service.ServiceFactory;
import service.SubdivisionService;
import view.Window;
import view.component.Form;
import view.page.SubdivisionPage;

import java.awt.event.ActionEvent;

public class SaveSubdivisionAction extends Action {
    private Form<Subdivision> form;

    public SaveSubdivisionAction(Window window, Form<Subdivision> form) {
        super(window);
        this.form = form;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        Subdivision subdivision = form.getEntity();
        if(subdivision != null) {
            try {
                SubdivisionService service = ServiceFactory.getService(SubdivisionService.class);
                service.save(subdivision);
                service.close();
                window.setPage(new SubdivisionPage(window, subdivision));
                Window.message("Сообщение", "Подразделение успешно сохранёно");
            } catch(PersistentException exception) {
                Window.message("Ошибка", "Невозможно сохранить подразделение");
            }
        }
    }
}
