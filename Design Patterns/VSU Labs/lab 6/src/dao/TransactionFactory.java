package dao;

import dao.csv.TransactionImpl;
import exception.PersistentException;

public class TransactionFactory {
	public static Transaction createTransaction() throws PersistentException {
		return new TransactionImpl();
	}
}