package dao.csv;

import dao.*;
import entity.Entity;
import entity.Equipment;
import exception.PersistentException;

import java.io.File;
import java.io.IOException;
import java.util.Collection;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class TransactionImpl extends Transaction {
	public static final File FOLDER = new File("storage");
	public static final String EXTENSION = ".csv";
	public static final String PREFIX = "tmp";
	public static final String SEPARATOR = "-";

	private static final Map<Class<? extends DAO<?>>, Class<? extends DAO<?>>> CLASSES = new ConcurrentHashMap<Class<? extends DAO<?>>, Class<? extends DAO<?>>>();
	private static final Map<Class<? extends DAO<?>>, File> FILES = new ConcurrentHashMap<Class<? extends DAO<?>>, File>();

	static {
		CLASSES.put(SubdivisionDAO.class, SubdivisionDAOImpl.class);
		FILES.put(SubdivisionDAOImpl.class, new File(FOLDER, "subdivisions.csv"));
		CLASSES.put(EquipmentDAO.class, EquipmentDAOImpl.class);
		FILES.put(EquipmentDAOImpl.class, new File(FOLDER, "equipments.csv"));
		CLASSES.put(WorkingDAO.class, WorkingDAOImpl.class);
		FILES.put(WorkingDAOImpl.class, new File(FOLDER, "workings.csv"));
	}

	private Map<File, File> changes = new HashMap<File, File>();

	@SuppressWarnings("unchecked")
	@Override
	public <Type extends DAO<? extends Entity>> Type createDao(Class<Type> key) throws PersistentException {
		Class<? extends DAO<?>> value = CLASSES.get(key);
		File file = FILES.get(value);
		if(value != null && file != null) {
			file = lastVersion(file);
			try {
				File tmp = temp(file);
				DAO<?> dao = value.getConstructor(File.class, File.class).newInstance(file, tmp);
				changes.put(file, tmp);
				return (Type)dao;
			} catch(Exception e) {
				throw new PersistentException(e);
			}
		}
		return null;
	}

	@Override
	public void commit() throws PersistentException {
		Collection<File> files = FILES.values();
		for(File file : files) {
			if(changes.containsKey(file)) {
				File tmp = lastVersion(file);
				if(!tmp.equals(file)) {
					file.delete();
					tmp.renameTo(file);
				}
			}
		}
		rollback();
	}

	@Override
	public void rollback() throws PersistentException {
		Collection<File> files = changes.values();
		for(File tmp : files) {
			if(tmp.exists()) {
				tmp.delete();
			}
		}
		changes.clear();
	}

	@Override
	public void close() {
		changes = null;
	}

	private File temp(File file) throws IOException {
		StringBuilder prefix = new StringBuilder(1024);
		prefix.append(PREFIX).append(SEPARATOR).append(file.getName()).append(SEPARATOR);
		File tmp = File.createTempFile(prefix.toString(), EXTENSION, FOLDER);
		tmp.delete();
		return tmp;
	}

	private File lastVersion(File file) {
		File last = file;
		while(changes.containsKey(file)) {
			file = changes.get(file);
			if(file.exists()) {
				last = file;
			}
		}
		return last;
	}
}
