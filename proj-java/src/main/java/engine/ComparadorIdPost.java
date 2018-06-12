package engine;


import java.util.Comparator;
public class ComparadorIdPost implements Comparator<Posts>
{
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
