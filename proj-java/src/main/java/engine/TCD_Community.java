package engine;


import java.util.Map;
import java.util.TreeMap;
import java.util.TreeSet;
import java.util.HashMap;
import java.util.stream.Collectors;

/*
 * Classe da estrutura principal TCD_Community
 * @author Grupo 32
 * @version 12/06/2018
 */

public class TCD_Community {
    /** TreeMap que guarda os posts organizados pelo seu id */
    private TreeMap<Long, Posts> arvPostsID;
    /** HashMap que armazena os utilizadores organizados pelo seu id*/
    private HashMap<Long, Users> tabUsers;
    /** HashMap que associa cada tag ao seu respetivo id */
    private HashMap<String, Long> tabTags;

    /**
     * Construtor vazio
     */
    public TCD_Community (){
        this.arvPostsID = new TreeMap<>();
        this.tabUsers = new HashMap<>();
        this.tabTags = new HashMap<>();
    }

    /**
     * Construtor parametrizado
     */
    public TCD_Community (TreeMap<Long, Posts> arvID, HashMap<Long, Users> tab, HashMap<String, Long> tags){
        setArvPostsID(arvID);
        setTabUsers(tab);
        setTabTags(tags);
    }

    /**
     * Construtor por cópia
     */
    public TCD_Community (TCD_Community com){
        this.arvPostsID = com.getArvPostsID();
        this.tabUsers = com.getTabUsers();
        this.tabTags = com.getTabTags();
    }


    /**
     * Método que obtém a árvore dos posts
     * @return os posts
     */
    public TreeMap<Long, Posts> getArvPostsID(){
        TreeMap<Long, Posts> res = new TreeMap<>();
        for(Posts p : this.arvPostsID.values())
            res.put(p.getIdPost(),p.clone());
        return res;
    }

    /**
     * Método que obtém a tabela dos utilizadores
     * @return os utilizadores
     */
    public HashMap<Long,Users> getTabUsers(){
        HashMap<Long,Users> res = new HashMap<>();
        for(Users u : this.tabUsers.values())
            res.put(u.getId(),u.clone());
        return res;
    }

    /**
     * Método que obtém as tags e os seus respetivos ids
     * @return as tags
     */
    public HashMap<String,Long> getTabTags(){
        HashMap<String,Long> res = new HashMap<>();
        for(Map.Entry<String,Long> t : this.tabTags.entrySet())
            res.put(t.getKey(),t.getValue());
        return res;
    }



    /**
     * Método que atualiza a árvore dos posts
     */
    public void setArvPostsID(TreeMap<Long,Posts> postsID){
        this.arvPostsID = new TreeMap<>();
        postsID.values().forEach(p -> this.arvPostsID.put(p.getIdPost(),p.clone()));
    }

    /**
     * Método que atualiza a tabela dos utilizadores
     */
    public void setTabUsers(HashMap<Long, Users> tab){
        this.tabUsers = new HashMap<>();
        tab.values().forEach(u -> this.tabUsers.put(u.getId(), u.clone()));
    }

    /**
     * Método que atualiza a tabela das tags
     */
    public void setTabTags(HashMap<String, Long> tab){
        this.tabTags = new HashMap<>();
        for(Map.Entry<String,Long> t : this.tabTags.entrySet())
            this.tabTags.put(t.getKey(), t.getValue());
    }

    /**
     * Devolve uma cópia de uma TCD_Community
     */
    public TCD_Community clone(){
        return new TCD_Community(this);
    }


    /**
     * Verifica a igualdade com outra TCD_Community
     */
    public boolean equals(Object o){
        if(o == this) return true;
        if(o == null || o.getClass() != this.getClass()) return false;

        TCD_Community com = (TCD_Community) o;

        return (this.arvPostsID.equals(com.getArvPostsID()) && this.tabUsers.equals(com.getTabUsers())
                        && this.tabTags.equals(com.getTabTags()));
    }

    /**
     * Devolve representação textual da TCD_Community
     */
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("\nPosts(ordenados pelo ID): ").append(this.arvPostsID.toString());
        sb.append("\nUtilizadores: ").append(this.tabUsers.toString());
        sb.append("\nTags: ").append(this.tabTags.toString());
        return sb.toString();
    }

    /**
     * Método que insere os posts nos utilizadores
     */
    public void inserePosts(){
        for(Posts p : this.arvPostsID.values())
            p.inserePostDoUser(this.tabUsers);
    }
}
