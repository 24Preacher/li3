package engine;

import java.util.Comparator;

/*
 * Classe do Comparador por Data dos posts
 * @author Grupo 32
 * @version 12/06/2018
 */
public class ComparadorDataPost  implements Comparator<Posts> {

    /*
     * Método que compara dois posts pela sua data
     */
    public int compare(Posts p1, Posts p2){
        int res;

        if(p1.getData().isAfter(p2.getData()))
            res = 1;
        else if(p1.getData().isBefore(p2.getData()))
            res = -1;
        else return p1.getTitulo().compareTo(p2.getTitulo());

        return res;
    }
}
