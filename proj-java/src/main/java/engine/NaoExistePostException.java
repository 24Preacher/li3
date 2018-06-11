package engine;


public class NaoExistePostException extends Exception
{
    public NaoExistePostException() {
        super();
    }
    public NaoExistePostException(String message) {
        super(message);
    }
}
