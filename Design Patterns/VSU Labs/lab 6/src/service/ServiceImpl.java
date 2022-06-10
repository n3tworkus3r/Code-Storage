package service;

import dao.Transaction;

abstract public class ServiceImpl implements Service {
	private Transaction transaction = null;

	public ServiceImpl(Transaction transaction) {
		this.transaction = transaction;
	}

	public Transaction getTransaction() {
		return transaction;
	}

	@Override
	public void close() {
		transaction.close();
	}
}