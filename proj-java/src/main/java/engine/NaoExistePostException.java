package engine;

/*
 * Classe que implementa a exceção de um post não existir
 * @author Grupo 32
 * @version 12/06/2018
 */


public class NaoExistePostException extends Exception
{
    /**
     * Construtor vazio
     */
    public NaoExistePostException() {
        super();
    }
    /**
     * Construtor parametrizado
     */
    public NaoExistePostException(String message) {
        super(message);
    }
}
