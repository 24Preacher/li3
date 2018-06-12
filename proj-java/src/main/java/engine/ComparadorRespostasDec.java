package engine;

import java.util.Comparator;

/*
 * Classe do Comparador por número de respostas decrescente dos posts
 * @author Grupo 32
 * @version 12/06/2018
 */

public class ComparadorRespostasDec implements Comparator<Posts> {

    /*
     * Método que compara dois posts pelo seu número de respostas
     */
    public int compare(Posts p1, Posts p2){
        int res;
        if(p1.getRespostas() > p2.getRespostas())
            res = -1;
        else if (p1.getRespostas() < p2.getRespostas())
            res = 1;
        else return p1.getTitulo().compareTo(p2.getTitulo());

        return res;
    }
}
