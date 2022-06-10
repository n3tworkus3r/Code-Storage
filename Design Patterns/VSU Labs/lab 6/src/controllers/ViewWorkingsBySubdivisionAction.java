package controllers;

import entity.Subdivision;
import entity.Working;
import exception.PersistentException;
import service.ServiceFactory;
import service.WorkingService;
import view.Window;
import view.component.Table;
import view.page.WorkingsPage;

import java.awt.event.ActionEvent;
import java.util.List;

public class ViewWorkingsBySubdivisionAction extends Action {
    private Table<Subdivision> table;

    public ViewWorkingsBySubdivisionAction(Window window, Table<Subdivision> table) {
        super(window);
        this.table = table;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        Subdivision subdivision = table.getSelectedEntity();
        if(subdivision != null) {
            try {
                WorkingService service = ServiceFactory.getService(WorkingService.class);
                List<Working> workings = service.findBySubdivision(subdivision);
                service.close();
                window.setPage(new WorkingsPage(window, workings));
            } catch(PersistentException exception) {
                Window.message("Ошибка", "Невозможно прочитать список эксплуатации оборудования");
            }
        }
    }
}
