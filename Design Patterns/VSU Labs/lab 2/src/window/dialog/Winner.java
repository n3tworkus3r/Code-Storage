package window.dialog;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Winner extends JDialog {

    public Winner(JFrame owner) {
        JDialog jDialog = new JDialog(owner, "Вы победили", true);

        add(new JLabel(
                        "Вы победили"),
                BorderLayout.CENTER);


        JButton exit = new JButton("Выход");
        exit.addActionListener(new ActionListener() {

            public void actionPerformed(ActionEvent event) {
                System.exit(0);
            }
        });


        JPanel panel = new JPanel();
        panel.add(exit);
        add(panel, BorderLayout.SOUTH);
        setSize(260, 160);
        setLocationRelativeTo(null);
        //setLocation(250,250);
    }
}

