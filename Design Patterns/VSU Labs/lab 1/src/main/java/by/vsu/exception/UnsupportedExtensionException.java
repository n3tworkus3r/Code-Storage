package by.vsu.exception;

public class UnsupportedExtensionException extends RuntimeException {

    public UnsupportedExtensionException(String message) {
        super(message);
    }

    public UnsupportedExtensionException(String message, Throwable cause) {
        super(message, cause);
    }

    public UnsupportedExtensionException(Throwable cause) {
        super(cause);
    }

    protected UnsupportedExtensionException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }

}
