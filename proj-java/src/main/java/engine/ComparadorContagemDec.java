package engine;

import common.Pair;
import java.util.Comparator;

public class ComparadorContagemDec implements Comparator<Pair<String,Long>> {

    public int compare(Pair<String, Long> p1, Pair<String, Long> p2){
        int res;

        if(p1.getSnd() > p2.getSnd())
            res = -1;
        else if (p1.getSnd() < p2.getSnd())
            res = 1;
        else return p1.getFst().compareTo(p2.getFst());

        return res;
    }
}
