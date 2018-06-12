package engine;


import java.util.Comparator;


public class ComparadorVotosDec implements Comparator<Posts> {

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
