package engine;

/*
 * Classe do Comparador por ID dos posts
 * @author Grupo 32
 * @version 12/06/2018
 */
import java.util.Comparator;

public class ComparadorIdPost implements Comparator<Posts>
{
    /*
     * Método que compara dois posts pela seu id
     */
    public int compare(Posts p1, Posts p2){
        int res;

        if(p1.getIdPost() > p2.getIdPost())
            res = 1;
        else if(p1.getIdPost() < p2.getIdPost())
            res = -1;
        else return p1.getTitulo().compareTo(p2.getTitulo());

        return res;
    }
}
