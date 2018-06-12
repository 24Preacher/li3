package engine;


import java.util.Comparator;
public class ComparadorRespostasDec implements Comparator<Posts> {

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
