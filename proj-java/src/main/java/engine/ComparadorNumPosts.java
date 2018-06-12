package engine;


import java.util.Comparator;

/*
 * Classe do Comparador por número de posts descrescente dos Utilizadores
 * @author Grupo 32
 * @version 12/06/2018
 */

public class ComparadorNumPosts implements Comparator<Users> {

    /*
     * Método que compara dois utilizadores pelo seu número de posts
     */
    public int compare(Users u1, Users u2){
        int res;
        if(u1.getPostsUser().size() > u2.getPostsUser().size())
            res = -1;
        else if (u1.getPostsUser().size() < u2.getPostsUser().size())
            res = 1;
        else return u1.getNome().compareTo(u2.getNome());

        return res;
    }
}
