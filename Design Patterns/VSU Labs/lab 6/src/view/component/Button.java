package view.component;

import controllers.Action;

import java.awt.*;

public class Button extends java.awt.Button {
	public Button(String text, Action action) {
		super(text);
		setPreferredSize(new Dimension(150, 25));
		addActionListener(action);
	}
}
