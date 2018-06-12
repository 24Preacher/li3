package engine;

/*
 * Classe que implementa a exceção de um utilizador não existir
 * @author Grupo 32
 * @version 12/06/2018
 */


public class NaoExisteUserException extends Exception
{
    /**
     * Construtor vazio
     */
    public NaoExisteUserException() {
        super();
    }
    /**
     * Construtor parametrizado
     */
    public NaoExisteUserException(String message) {
        super(message);
    }
}
