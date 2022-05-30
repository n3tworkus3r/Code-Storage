package by.vsu.exception;

public class ExtensionNotFoundException extends RuntimeException  {

    public ExtensionNotFoundException(String message) {
        super(message);
    }

    public ExtensionNotFoundException(String message, Throwable cause) {
        super(message, cause);
    }

    public ExtensionNotFoundException(Throwable cause) {
        super(cause);
    }

    protected ExtensionNotFoundException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }

}
