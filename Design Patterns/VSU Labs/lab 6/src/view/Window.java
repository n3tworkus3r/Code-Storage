package view;

import java.awt.BorderLayout;
import java.awt.Button;
import java.awt.Dialog;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Frame;
import java.awt.GraphicsConfiguration;
import java.awt.GraphicsEnvironment;
import java.awt.Insets;
import java.awt.Label;
import java.awt.Menu;
import java.awt.MenuBar;
import java.awt.MenuItem;
import java.awt.Panel;
import java.awt.Rectangle;
import java.awt.SystemColor;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import controllers.ViewEquipmentsAction;
import controllers.ViewSubdivisionsAction;
import controllers.ViewWorkingsAction;

public class Window extends Frame {
    private static Window main;

    public Window() {
        super("Оборудование предприятия");
        MenuBar menuBar = new MenuBar();
        Menu menu = new Menu("Страницы");
        MenuItem workings = new MenuItem("Эксплуатация оборудования");
        workings.addActionListener(new ViewWorkingsAction(this));
        menu.add(workings);
        MenuItem equipments = new MenuItem("Оборудование");
        equipments.addActionListener(new ViewEquipmentsAction(this));
        menu.add(equipments);
        MenuItem subdivisions = new MenuItem("Подразделение");
        subdivisions.addActionListener(new ViewSubdivisionsAction(this));
        menu.add(subdivisions);
        menuBar.add(menu);
        setMenuBar(menuBar);
        Rectangle formSize = calcFormSize();
        setBounds(formSize);
        setBackground(SystemColor.menu);
        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                System.exit(0);
            }
        });
        setVisible(true);
        validate();
    }

    public void setPage(Page page) {
        removeAll();
        add(page);
        validate();
    }

    public static void main(String[] arguments) {
        main = new Window();
        MenuItem item = main.getMenuBar().getMenu(0).getItem(0);
        ActionEvent event = new ActionEvent(item, 0, item.getActionCommand());
        ActionListener[] listeners = item.getActionListeners();
        for(ActionListener listener : listeners) {
            listener.actionPerformed(event);
        }
    }

    private static Rectangle screen;

    private static Rectangle calcFormSize() {
        GraphicsConfiguration configuration = GraphicsEnvironment.getLocalGraphicsEnvironment().getDefaultScreenDevice().getDefaultConfiguration();
        Insets insets = java.awt.Toolkit.getDefaultToolkit().getScreenInsets(configuration);
        screen = configuration.getBounds();
        screen.x -= insets.left;
        screen.y -= insets.top;
        screen.width -= insets.right;
        screen.height -= insets.bottom;
        return new Rectangle(screen.x + screen.width * 19 / 100, screen.y + screen.height * 19 / 100, screen.width * 62 / 100, screen.height * 62 / 100);
    }

    public static void message(String title, String message) {
        final Dialog dialog = new Dialog(main, title);
        dialog.setModal(true);
        dialog.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                dialog.setVisible(false);
            }
        });
        dialog.setBounds(screen.x + screen.width * 3822 / 10000, screen.y + screen.height * 3822 / 10000, screen.width * 3500 / 10000, screen.height * 2356 / 10000);
        dialog.setLayout(new BorderLayout());
        dialog.add(new Label(message, Label.CENTER), BorderLayout.CENTER);
        Panel panel = new Panel(new FlowLayout(FlowLayout.CENTER, 10, 10));
        Button button = new Button("OK");
        button.setPreferredSize(new Dimension(100, 25));
        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent arg0) {
                dialog.setVisible(false);
            }
        });
        panel.add(button);
        dialog.add(panel, BorderLayout.SOUTH);
        dialog.setVisible(true);
    }
}
