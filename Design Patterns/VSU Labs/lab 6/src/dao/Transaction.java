package dao;

import entity.Entity;
import exception.PersistentException;

abstract public class Transaction {
	abstract public <Type extends DAO<? extends Entity>> Type createDao(Class<Type> key) throws PersistentException;

	abstract public void commit() throws PersistentException;

	abstract public void rollback() throws PersistentException;

	abstract public void close();
}