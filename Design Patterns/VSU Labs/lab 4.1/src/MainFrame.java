import java.awt.Insets;

import javax.swing.JFrame;

public class MainFrame extends JFrame {
	public MainFrame(String title, int width, int height, Picture picture) {
		super("Рисунок");
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		add(picture);
		setVisible(true);
		setResizable(false);
		Insets insets = getInsets();
		setSize(width + insets.left + insets.right, height + insets.top + insets.bottom);
		setLocationRelativeTo(null);
	}
}
