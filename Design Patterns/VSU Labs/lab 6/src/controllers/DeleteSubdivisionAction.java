package controllers;

import entity.Subdivision;
import exception.IntegrityViolationException;
import exception.PersistentException;
import service.ServiceFactory;
import service.SubdivisionService;
import view.Window;
import view.component.Form;
import view.page.SubdivisionPage;

import java.awt.event.ActionEvent;

public class DeleteSubdivisionAction extends Action {
    private Form<Subdivision> form;

    public DeleteSubdivisionAction(Window window, Form<Subdivision> form) {
        super(window);
        this.form = form;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        Subdivision subdivision = form.getEntity();
        if(subdivision != null) {
            try {
                SubdivisionService service = ServiceFactory.getService(SubdivisionService.class);
                service.delete(subdivision.getIdentity());
                service.close();
                window.setPage(new SubdivisionPage(window, null));
                Window.message("Сообщение", "Структурное подразделение успешно удалёно");
            } catch(IntegrityViolationException exception) {
                Window.message("Ошибка", "Невозможно удалить подраздение из-за его эксплуатации");
            } catch(PersistentException exception) {
                Window.message("Ошибка", "Невозможно удалить подразделение");
            }
        }
    }
}
