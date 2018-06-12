package engine;

import java.util.Comparator;

/*
 * Classe do Comparador por reputação decrescente dos utilizadores
 * @author Grupo 32
 * @version 12/06/2018
 */
public class ComparadorReputacaoDec implements Comparator<Users> {

    /*
     * Método que compara dois utilizadores pela sua reputação
     */
    public int compare(Users u1, Users u2){
        int res;

        if(u1.getReputacao() > u2.getReputacao())
            res = -1;
        else if(u1.getReputacao() < u2.getReputacao())
            res = 1;
        else return u1.getNome().compareTo(u2.getNome());

        return res;
    }
}
