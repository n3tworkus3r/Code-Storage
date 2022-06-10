package controllers;

import view.Window;

import java.awt.event.ActionListener;

public abstract class Action implements ActionListener {
	protected Window window;

	public Action(Window window) {
		this.window = window;
	}
}
