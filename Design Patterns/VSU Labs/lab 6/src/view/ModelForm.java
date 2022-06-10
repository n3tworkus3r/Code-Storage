package view;

import entity.Entity;

import java.awt.*;
import java.util.LinkedHashMap;

abstract public class ModelForm<Type extends Entity> {
	private LinkedHashMap<String, Component> fields;
	private Integer identity;

	public ModelForm(Type entity) {
		this.fields = createFields(entity);
		identity = entity != null ? entity.getIdentity() : null;
	}

	public LinkedHashMap<Label, Component> getFields() {
		LinkedHashMap<Label, Component> result = new LinkedHashMap<Label, Component>();
		for(String label : fields.keySet()) {
			result.put(new Label(label, Label.RIGHT), fields.get(label));
		}
		return result;
	}

	public Type getEntity() {
		Type entity = createEntity(fields);
		if(entity != null) {
			entity.setIdentity(identity);
		}
		return entity;
	}

	abstract protected LinkedHashMap<String, Component> createFields(Type entity);

	abstract protected Type createEntity(LinkedHashMap<String, Component> fields);
}
