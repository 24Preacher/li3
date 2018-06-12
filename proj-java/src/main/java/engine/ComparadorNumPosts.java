package engine;


import java.util.Comparator;

public class ComparadorNumPosts implements Comparator<Users> {

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
