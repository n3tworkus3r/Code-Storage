package exception;

public class IntegrityViolationException extends PersistentException {
	public IntegrityViolationException(Throwable e) {
		super(e);
	}

	public IntegrityViolationException() {
	}
}
