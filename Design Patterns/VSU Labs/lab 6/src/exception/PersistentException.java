package exception;

public class PersistentException extends Exception {
	public PersistentException(Throwable e) {
		super(e);
	}

	public PersistentException() {
	}
}