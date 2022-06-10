package dao.csv;

import dao.DAO;
import entity.Entity;
import exception.PersistentException;

import java.io.*;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.List;

abstract public class BaseDAOImpl<Type extends Entity> implements DAO<Type> {
	private File file;
	private File temp;

	public BaseDAOImpl(File file, File temp) {
		this.file = file;
		this.temp = temp;
	}

	private CSVReader getReader() throws IOException {
		try {
			return new CSVReader(new FileInputStream(file));
		} catch(FileNotFoundException e) {
			return null;
		}
	}

	private CSVWriter getWriter() throws IOException {
		return new CSVWriter(new FileOutputStream(temp));
	}

	abstract protected Type read(CSVReader reader) throws IOException, ParseException;

	abstract protected void write(Type entity, CSVWriter writer) throws IOException;

	public Integer create(Type entity) throws PersistentException {
		CSVReader reader = null;
		CSVWriter writer = null;
		try {
			reader = getReader();
			writer = getWriter();
			Integer maxIdentity = 0;
			Type type = null;
			while((type = read(reader)) != null) {
				if(type.getIdentity() > maxIdentity) {
					maxIdentity = type.getIdentity();
				}
				write(type, writer);
			}
			entity.setIdentity(maxIdentity + 1);
			write(entity, writer);
			return entity.getIdentity();
		} catch(IOException e) {
			throw new PersistentException(e);
		} catch (ParseException e) {
			throw new PersistentException(e);
		} finally {
			try {
				reader.close();
			} catch(Exception e) {
			}
			try {
				writer.close();
			} catch(Exception e) {
			}
		}
	}

	@Override
	public Type read(Integer identity) throws PersistentException {
		CSVReader reader = null;
		try {
			reader = getReader();
			Type type = null;
			while((type = read(reader)) != null) {
				if(type.getIdentity().equals(identity)) {
					return type;
				}
			}
			return null;
		} catch (IOException e) {
			throw new PersistentException(e);
		} catch (ParseException e) {
			throw new PersistentException(e);
		} finally {
			try {
				reader.close();
			} catch(Exception e) {
			}
		}
	}

	@Override
	public void update(Type entity) throws PersistentException {
		CSVReader reader = null;
		CSVWriter writer = null;
		try {
			reader = getReader();
			writer = getWriter();
			Type type = null;
			while((type = read(reader)) != null) {
				if(type.equals(entity)) {
					write(entity, writer);
				} else {
					write(type, writer);
				}
			}
		} catch(IOException e) {
			throw new PersistentException(e);
		} catch (ParseException e) {
			throw new PersistentException(e);
		} finally {
			try {
				reader.close();
			} catch(Exception e) {
			}
			try {
				writer.close();
			} catch(Exception e) {
			}
		}
	}

	@Override
	public void delete(Integer identity) throws PersistentException {
		CSVReader reader = null;
		CSVWriter writer = null;
		try {
			reader = getReader();
			writer = getWriter();
			Type type = null;
			while((type = read(reader)) != null) {
				if(!type.getIdentity().equals(identity)) {
					write(type, writer);
				}
			}
		} catch(IOException e) {
			throw new PersistentException(e);
		} catch (ParseException e) {
			throw new PersistentException(e);
		} finally {
			try {
				reader.close();
			} catch(Exception e) {
			}
			try {
				writer.close();
			} catch(Exception e) {
			}
		}
	}

	protected interface Filter<Type extends Entity> {
		boolean check(Type type);
	}

	protected List<Type> read(Filter<Type> filter) throws PersistentException {
		List<Type> types = new ArrayList<Type>();
		CSVReader reader = null;
		try {
			reader = getReader();
			Type type = null;
			while((type = read(reader)) != null) {
				if(filter.check(type)) {
					types.add(type);
				}
			}
			return types;
		} catch (IOException e) {
			throw new PersistentException(e);
		} catch (ParseException e) {
			throw new PersistentException(e);
		} finally {
			try {
				reader.close();
			} catch(Exception e) {
			}
		}
	}
}
