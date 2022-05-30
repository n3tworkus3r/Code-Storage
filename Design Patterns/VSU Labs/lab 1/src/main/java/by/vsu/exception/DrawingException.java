package by.vsu.exception;

public class DrawingException extends RuntimeException {

    public DrawingException(String message, Throwable cause) {
        super(message, cause);
    }

    public DrawingException(Throwable cause) {
        super(cause);
    }

    protected DrawingException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }

}
