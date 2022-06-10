package view.component;

import entity.Entity;
import view.ModelForm;

import java.awt.*;
import java.util.LinkedHashMap;

public class Form<Type extends Entity> extends Panel {
	private ModelForm<Type> model;

	public Form(ModelForm<Type> model, String caption) {
		super(new BorderLayout());
		this.model = model;
		LinkedHashMap<Label, Component> map = model.getFields();
		add(new Label(caption, Label.CENTER), BorderLayout.NORTH);
		GridBagLayout layout = new GridBagLayout();
		layout.columnWeights = new double[] {1};
		layout.rowHeights = new int[map.size()];
		for(int i = 0; i < layout.rowHeights.length; i++) {
			layout.rowHeights[i] = 25;
		}
		GridBagConstraints constraints = new GridBagConstraints();
		constraints.fill = GridBagConstraints.HORIZONTAL;
		constraints.insets = new Insets(5, 5, 5, 5);
		constraints.gridx = 0;
		Panel left = new Panel();
		left.setLayout(layout);
		Panel center = new Panel();
		center.setLayout(layout);
		constraints.gridy = 0;
		for(Label label : map.keySet()) {
			left.add(label, constraints);
			center.add(map.get(label), constraints);
			constraints.gridy++;
		}
		add(left, BorderLayout.WEST);
		add(center, BorderLayout.CENTER);
	}

	public Type getEntity() {
		return model.getEntity();
	}
}
