package by.vsu;

import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import java.awt.BorderLayout;
import java.awt.GridLayout;

import static javax.swing.SwingConstants.CENTER;

public class MainWindow extends JFrame {

    private String filename;

    private JLabel pathLabel;

    private JFileChooser fileChooser;

    public MainWindow() {
        super("Primitive drawler");

        initializeFileChooser();

        JPanel buttonsPanel = new JPanel(new GridLayout());

        buttonsPanel.add(initPathLabel());
        buttonsPanel.add(initializeDrawButton());
        buttonsPanel.add(initializeChoosePathButton());

        add(buttonsPanel, BorderLayout.CENTER);

        setSize(640, 360);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    public static void main(String[] args) {
        MainWindow mainWindow = new MainWindow();
        mainWindow.setVisible(true);
    }

    public void initializeFileChooser() {
        fileChooser = new JFileChooser();
    }

    public JLabel initPathLabel() {
        pathLabel = new JLabel("Path:");
        pathLabel.setHorizontalAlignment(CENTER);
        pathLabel.setText("empty");

        return pathLabel;
    }

    public JButton initializeDrawButton() {
        JButton drawButton = new JButton("Draw");
        drawButton.addActionListener(e -> {
            new DrawWindow(filename);
        });

        return drawButton;
    }

    public JButton initializeChoosePathButton() {
        JButton chooseFileButton = new JButton("Choose file");
        chooseFileButton.addActionListener(e -> {
            int result = fileChooser.showOpenDialog(MainWindow.this);
            fileChooser.setDialogTitle("Choose file");

            if (result == JFileChooser.APPROVE_OPTION ) {
                filename = fileChooser.getSelectedFile().getAbsolutePath();
                pathLabel.setText(filename);
            }
        });

        return chooseFileButton;
    }

}
