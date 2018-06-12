package engine;


import java.util.Set;
import java.util.TreeSet;

/*
 * Classe dos Users
 * @author Grupo 32
 * @version 12/06/2018
 */

public class Users {

    /** Id do utilizador */
    private long id;
    /** Nome do utilizador */
    private String nome;
    /** Biografia do utilizador */
    private String bio;
    /** Reputação do utilizador */
    private int reputacao;
    /** Posts do utilizador */
    private Set<Posts> postsUser;

    /**
     * Construtor vazio
     */
    public Users (){
        this.id = 0;
        this.nome = "n/a";
        this.bio = "n/a";
        this.reputacao = 0;
        this.postsUser = new TreeSet<>(new ComparadorDataPost());
    }

    /**
     * Construtor parametrizado
     */
    public Users(long id, String nome, String bio, int rep, Set<Posts> p){
        this.id = id;
        this.nome = nome;
        this.bio = bio;
        this.reputacao = rep;
        setPostsUser(p);
    }

    /**
     * Construtor por cópia
     */
    public Users(Users u){
        this.id = u.getId();
        this.nome = u.getNome();
        this.bio = u.getBio();
        this.reputacao = u.getReputacao();
        this.postsUser = u.getPostsUser();
    }

    /**
     * Método que obtém o id do utilizador
     * @return o id
     */
    public long getId(){
        return this.id;
    }

    /**
     * Método que obtém o nome do utilizador
     * @return o nome
     */
    public String getNome(){
        return this.nome;
    }

    /**
     * Método que obtém a biografia do utilizador
     * @return a biografia
     */
    public String getBio(){
        return this.bio;
    }

    /**
     * Método que obtém a reputação do utilizador
     * @return a reputação
     */
    public int getReputacao(){
        return this.reputacao;
    }

    /**
     * Método que obtém os posts do utilizador
     * @return os posts
     */
    public Set<Posts> getPostsUser(){
        Set<Posts> res = new TreeSet<>(new ComparadorDataPost());
        this.postsUser.stream().map(Posts::clone).forEach(res::add);
        return res;
    }


    /**
     * Método que atualiza o id do utilizador
     */
    public void setId(long id){
        this.id = id;
    }

    /**
     * Método que atualiza o nome do utilizador
     */
    public void setNome(String nome){
        this.nome = nome;
    }

    /**
     * Método que atualiza a biografia do utilizador
     */
    public void setBio(String bio){
        this.bio = bio;
    }

    /**
     * Método que atualiza a reputação do utilizador
     */
    public void setReputacao(int rep){
        this.reputacao = rep;
    }

    /**
     * Método que atualiza os posts do utilizador
     */
    public void setPostsUser(Set<Posts> newPosts){
        this.postsUser = new TreeSet<>(new ComparadorDataPost());
        newPosts.forEach(p -> this.postsUser.add(p.clone()));
    }


    /**
     * Devolve uma cópia de um utilizador
     */
    public Users clone(){
        return new Users(this);
    }


    /**
     * Verifica a igualdade com outro utilizador
     */
    public boolean equals(Object o){
        if(o == this) return true;
        if(o == null || o.getClass() != this.getClass()) return false;

        Users u = (Users) o;

        return (this.id == u.getId() && this.nome.equals(u.getNome()) && this.bio.equals(u.getBio()) &&
                this.reputacao == u.getReputacao() && this.postsUser.equals(u.getPostsUser()));
    }

    /**
     * Devolve representação textual do utilizador
     */
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
