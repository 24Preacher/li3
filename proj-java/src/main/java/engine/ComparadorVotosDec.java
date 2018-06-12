package engine;

import java.util.Comparator;

/*
 * Classe do Comparador por número de votos decrescente dos posts
 * @author Grupo 32
 * @version 12/06/2018
 */

public class ComparadorVotosDec implements Comparator<Posts> {

        /*
         * Método que compara dois posts pelo seu número de votos
         */
        public int compare(Posts p1, Posts p2){
            int res;
            if(p1.getVotos() > p2.getVotos())
                res = -1;
            else if (p1.getVotos() < p2.getVotos())
                res = 1;
            else return p1.getTitulo().compareTo(p2.getTitulo());

            return res;
        }
}
