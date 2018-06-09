package engine;


import java.util.TreeSet;
import java.util.HashMap;
import java.util.stream.Collectors;

public class TCD_Community {
    private TreeSet<Posts> arvPostsData;
    private TreeSet<Posts> arvPostsID;
    private HashMap<Long, Users> tabUsers;


    public TCD_Community (){
        this.arvPostsData = new TreeSet<>();
        this.arvPostsID = new TreeSet<>();
        this.tabUsers = new HashMap<>();
    }

    public TCD_Community (TreeSet<Posts> arvData, TreeSet<Posts> arvID, HashMap<Long, Users> tab){
        setArvPostsID(arvID);
        setArvPostsData(arvData);
        setTabUsers(tab);
    }


    public TCD_Community (TCD_Community com){
        this.arvPostsData = com.getArvPostsData();
        this.arvPostsID = com.getArvPostsID();
        this.tabUsers = com.getTabUsers();
    }

    //GETS

    public TreeSet<Posts> getArvPostsData(){
        TreeSet<Posts> res = new TreeSet<>(new ComparadorDataPost());
        this.arvPostsData.stream().map(Posts::clone).forEach(res::add);
        return res;
    }

    public TreeSet<Posts> getArvPostsID(){
        TreeSet<Posts> res = new TreeSet<>(new ComparadorIdPost());
        this.arvPostsID.stream().map(Posts::clone).forEach(res::add);
        return res;
    }

    public HashMap<Long,Users> getTabUsers(){
        HashMap<Long,Users> res = new HashMap<>();
        for(Users u : this.tabUsers.values())
            res.put(u.getId(),u.clone());
        return res;
    }

    //SETS

    public void setArvPostsData(TreeSet<Posts> postsData){
        this.arvPostsData = new TreeSet<>(new ComparadorDataPost());
        postsData.forEach(p -> this.arvPostsData.add(p.clone()));
    }

    public void setArvPostsID(TreeSet<Posts> postsID){
        this.arvPostsID = new TreeSet<>(new ComparadorIdPost());
        postsID.forEach(p -> this.arvPostsID.add(p.clone()));
    }

    public void setTabUsers(HashMap<Long, Users> tab){
        this.tabUsers = new HashMap<>();
        tab.values().forEach(u -> this.tabUsers.put(u.getId(), u.clone()));
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

        return (this.arvPostsData.equals(com.getArvPostsData()) && this.arvPostsID.equals(com.getArvPostsID())
                && this.tabUsers.equals(com.getTabUsers()));
    }

    //ToString

    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("\nPosts(ordenados pela Data): ").append(this.arvPostsData.toString());
        sb.append("\nPosts(ordenados pelo ID): ").append(this.arvPostsID.toString());
        sb.append("\nUtilizadores: ").append(this.tabUsers.toString());
        return sb.toString();
    }

    //Percorre os posts e insere os em cada user -- fazer no load
    public void inserePosts(){
        this.arvPostsData.forEach(p -> p.inserePostDoUser(this.tabUsers));
    }
}
