package engine;



import java.util.Map;
import java.util.TreeMap;
import java.util.TreeSet;
import java.util.HashMap;
import java.util.stream.Collectors;

public class TCD_Community {
    private TreeMap<Long, Posts> arvPostsID;
    private HashMap<Long, Users> tabUsers;
    private HashMap<String, Long> tabTags;


    public TCD_Community (){
        this.arvPostsID = new TreeMap<>();
        this.tabUsers = new HashMap<>();
        this.tabTags = new HashMap<>();
    }

    public TCD_Community (TreeMap<Long, Posts> arvID, HashMap<Long, Users> tab, HashMap<String, Long> tags){
        setArvPostsID(arvID);
        setTabUsers(tab);
        setTabTags(tags);
    }


    public TCD_Community (TCD_Community com){
        this.arvPostsID = com.getArvPostsID();
        this.tabUsers = com.getTabUsers();
        this.tabTags = com.getTabTags();
    }

    //GETS

    public TreeMap<Long, Posts> getArvPostsID(){
        TreeMap<Long, Posts> res = new TreeMap<>();
        for(Posts p : this.arvPostsID.values())
            res.put(p.getIdPost(),p.clone());
        return res;
    }

    public HashMap<Long,Users> getTabUsers(){
        HashMap<Long,Users> res = new HashMap<>();
        for(Users u : this.tabUsers.values())
            res.put(u.getId(),u.clone());
        return res;
    }

    public HashMap<String,Long> getTabTags(){
        HashMap<String,Long> res = new HashMap<>();
        for(Map.Entry<String,Long> t : this.tabTags.entrySet())
            res.put(t.getKey(),t.getValue());
        return res;
    }

    //SETS

    public void setArvPostsID(TreeMap<Long,Posts> postsID){
        this.arvPostsID = new TreeMap<>();
        postsID.values().forEach(p -> this.arvPostsID.put(p.getIdPost(),p.clone()));
    }

    public void setTabUsers(HashMap<Long, Users> tab){
        this.tabUsers = new HashMap<>();
        tab.values().forEach(u -> this.tabUsers.put(u.getId(), u.clone()));
    }

    public void setTabTags(HashMap<String, Long> tab){
        this.tabTags = new HashMap<>();
        for(Map.Entry<String,Long> t : this.tabTags.entrySet())
            this.tabTags.put(t.getKey(), t.getValue());
    }

    //CLONE
    public TCD_Community clone(){
        return new TCD_Community(this);
    }

    //EQUALS

    public boolean equals(Object o){
        if(o == this) return true;
        if(o == null || o.getClass() != this.getClass()) return false;

        TCD_Community com = (TCD_Community) o;

        return (this.arvPostsID.equals(com.getArvPostsID()) && this.tabUsers.equals(com.getTabUsers())
                        && this.tabTags.equals(com.getTabTags()));
    }

    //ToString

    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("\nPosts(ordenados pelo ID): ").append(this.arvPostsID.toString());
        sb.append("\nUtilizadores: ").append(this.tabUsers.toString());
        sb.append("\nTags: ").append(this.tabTags.toString());
        return sb.toString();
    }

    //Percorre os posts e insere os em cada user -- fazer no load
    public void inserePosts(){
        this.arvPostsID.values().forEach(p -> p.inserePostDoUser(this.tabUsers));
    }
}
