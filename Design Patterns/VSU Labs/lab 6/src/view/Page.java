package view;

import java.awt.*;

abstract public class Page extends Panel {
	protected Window window;

	public Page(Window window) {
		setLayout(new BorderLayout());
		this.window = window;
	}
}
