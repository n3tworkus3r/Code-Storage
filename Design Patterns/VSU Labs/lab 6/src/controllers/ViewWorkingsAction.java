package controllers;

import entity.Subdivision;
import entity.Working;
import exception.PersistentException;
import service.ServiceFactory;
import service.SubdivisionService;
import service.WorkingService;
import view.Window;
import view.page.SubdivisionsPage;
import view.page.WorkingsPage;

import java.awt.event.ActionEvent;
import java.util.ArrayList;
import java.util.List;

public class ViewWorkingsAction extends Action {
    public ViewWorkingsAction(Window window) {
        super(window);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        try {
            WorkingService service = ServiceFactory.getService(WorkingService.class);
            List<Working> workings = service.findAll();
            service.close();
            window.setPage(new WorkingsPage(window, workings));
        } catch (PersistentException exception) {
            Window.message("Ошибка", "Невозможно прочитать список эксплуатаций");
        }
    }
}
