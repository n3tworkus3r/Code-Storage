package window;

import javax.swing.*;

public class Window {
    protected static JPanel jPanel;
    protected static JFrame jFrame;
    private static final int width = 1000;
    private static final int height = 950;

    public Window(){
        this.jPanel = new JPanel();
        this.jFrame = new JFrame();

        jFrame.setTitle("Pyramid");
        jFrame.add(jPanel);
        jFrame.setSize(width, height);
        jFrame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        jPanel.setLayout(null);
        jFrame.setLocationRelativeTo(null);
        jFrame.setVisible(true);
    }

    public static JFrame getjFrame() {
        return jFrame;
    }

    public static void main(String[] args){
        Field.NewGame newGame = new Field.NewGame();

    }
}
