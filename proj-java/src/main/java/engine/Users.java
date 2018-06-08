package engine;


import java.util.List;
import java.util.ArrayList;

public class Users {

    private long id;
    private String nome;
    private String bio;
    private int reputacao;
    private List<Posts> postsUser; // por uma avl ordenada por data

    public Users (){
        this.id = 0;
        this.nome = "n/a";
        this.bio = "n/a";
        this.reputacao = 0;
        this.postsUser = new ArrayList<>();
    }

    public Users(long id, String nome, String bio, int rep, List<Posts> p){
        this.id = id;
        this.nome = nome;
        this.bio = bio;
        this.reputacao = rep;
        setPostsUser(p);
    }

    public Users(Users u){
        this.id = u.getId();
        this.nome = u.getNome();
        this.bio = u.getBio();
        this.reputacao = u.getReputacao();
        this.postsUser = u.getPostsUser();
    }

    //GETS

    public long getId(){
        return this.id;
    }

    public String getNome(){
        return this.nome;
    }

    public String getBio(){
        return this.bio;
    }

    public int getReputacao(){
        return this.reputacao;
    }

    public List<Posts> getPostsUser(){
        List<Posts> res = new ArrayList<>();
        for(Posts p : this.postsUser)
            res.add(p.clone());
        return res;
    }

    //SETS

    public void setId(long id){
        this.id = id;
    }

    public void setNome(String nome){
        this.nome = nome;
    }

    public void setBio(String bio){
        this.bio = bio;
    }

    public void setReputacao(int rep){
        this.reputacao = rep;
    }

    public void setPostsUser(List<Posts> newPosts){
        this.postsUser = new ArrayList<>();
        for(Posts p : newPosts)
            this.postsUser.add(p.clone());
    }

    //CLONE

    public Users clone(){
        return new Users(this);
    }

    //EQUALS

    public boolean equals(Object o){
        if(o == this) return true;
        if(o == null || o.getClass() != this.getClass()) return false;

        Users u = (Users) o;

        return (this.id == u.getId() && this.nome.equals(u.getNome()) && this.bio.equals(u.getBio()) &&
                this.reputacao == u.getReputacao() && this.postsUser.equals(u.getPostsUser()));
    }

    //ToString

    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("----USER----");
        sb.append("\nID: ").append(this.id);
        sb.append("\nNome: ").append(this.nome);
        sb.append("\nBiografia: ").append(this.bio);
        sb.append("\nReputacao").append(this.reputacao);
        sb.append("\nPosts: ").append(this.postsUser.toString());
        return sb.toString();
    }
}
