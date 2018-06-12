package engine;


import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.time.LocalDateTime;
import java.util.TreeSet;
import java.util.Set;

/*
* Classe dos Posts
* @author Grupo 32
* @version 12/06/2018
*/


public class Posts {
    /** Id do post */
    private long idPost;
    /** Id do autor do post */
    private long idAutor;
    /** Titulo do post */
    private String titulo;
    /** Data do post*/
    private LocalDateTime data;
    /** Tipo do post */
    private int postType;
    /** Id da pergunta caso o post seja uma resposta*/
    private long idPai;
    /** Número de comentários */
    private int comentarios;
    /** Número de respostas */
    private int respostas;
    /** Diferença entre votos positivos e negativos */
    private int votos;
    /** Lista das tags */
    private List<String> tags;

    /**
     * Construtor vazio
     */
    public Posts(){
        this.idPost = 0;
        this.idAutor = 0;
        this.titulo = "n/a";
        this.data = LocalDateTime.now();
        this.postType = 0;
        this.idPai = 0;
        this.comentarios = 0;
        this.respostas = 0;
        this.votos = 0;
        this.tags = new ArrayList<>();
    }

    /**
     * Construtor parametrizado
     */
    public Posts(long post, long user, String title, LocalDateTime date, int type, long parent, int com, int res, int vot, List<String> tags){
        this.idPost = post;
        this.idAutor = user;
        this.titulo = title;
        this.data = date;
        this.postType = type;
        this.idPai = parent;
        this.comentarios = com;
        this.respostas = res;
        this.votos = vot;
        setTags(tags);
    }

    /**
     * Construtor por cópia
     */
    public Posts(Posts p){
        this.idPost = p.getIdPost();
        this.idAutor = p.getIdAutor();
        this.titulo = p.getTitulo();
        this.data = p.getData();
        this.postType = p.getPostType();
        this.idPai = p.getIdPai();
        this.comentarios = p.getComentarios();
        this.respostas = p.getRespostas();
        this.votos = p.getVotos();
        this.tags = p.getTags();
    }

    /**
     * Método que obtém o id do post
     * @return o id
     */
    public long getIdPost(){
        return this.idPost;
    }

    /**
     * Método que obtém o id do autor do post
     * @return o id
     */
    public long getIdAutor(){
        return this.idAutor;
    }

    /**
     * Método que obtém o Título
     * @return o titulo
     */
    public String getTitulo(){
        return this.titulo;
    }

    /**
     * Método que obtém a data do post
     * @return a data
     */
    public LocalDateTime getData(){
        return this.data;
    }

    /**
     * Método que obtém o tipo do post
     * @return o tipo do post
     */
    public int getPostType(){
        return this.postType;
    }

    /**
     * Método que obtém o id da pergunta correspondente caso o post seja uma resposta
     * @return o id
     */
    public long getIdPai(){
        return this.idPai;
    }

    /**
     * Método que obtém o número de comentários
     * @return o número de comentários
     */
    public int getComentarios(){
        return this.comentarios;
    }

    /**
     * Método que obtém o número de respostas
     * @return o número de respostas
     */
    public int getRespostas(){
        return this.respostas;
    }

    /**
     * Método que obtém o número de votos
     * @return o número de votos
     */
    public int getVotos(){
        return this.votos;
    }

    /**
     * Método que obtém a lista das tags do post
     * @return as tags
     */
    public List<String> getTags(){
        List<String> res = new ArrayList<>();

        for(String s : this.tags)
            res.add(s);
        return res;
    }


    /**
     * Método que atualiza o id do post
     */
    public void setIdPost(long post){
        this.idPost = post;
    }

    /**
     * Método que atualiza o id do autor do post
     */
    public void setIdAutor(long user){
        this.idAutor = user;
    }

    /**
     * Método que atualiza o titulo do post
     */
    public void setTitulo(String title){
        this.titulo = title;
    }

    /**
     * Método que atualiza a data do post
     */
    public void setData(LocalDateTime d){
        this.data = d;
    }

    /**
     * Método que atualiza o tipo do post
     */
    public void setPostType(int type){
        this.postType = type;
    }

    /**
     * Método que atualiza o id da pergunta caso o post seja resposta
     */
    public void setIdPai(long pai){
        this.idPai = pai;
    }

    /**
     * Método que atualiza o número de comentários
     */
    public void setComentarios(int com){
        this.comentarios = com;
    }

    /**
     * Método que atualiza o número de respostas
     */
    public void setRespostas(int res){
        this.respostas = res;
    }

    /**
     * Método que atualiza o número de votos
     */
    public void setVotos(int votos){
        this.votos = votos;
    }

    /**
     * Método que atualiza a lista das tags do post
     */
    public void setTags(List<String> novasTags){
        this.tags = new ArrayList<>();
        for(String s : novasTags)
            this.tags.add(s);
    }


    /**
     * Devolve uma cópia de um post
     */
    public Posts clone(){
        return new Posts(this);
    }


    /**
    * Verifica a igualdade com outro post
    */
    public boolean equals(Object o){
        if(o == this) return true;
        if(o == null || o.getClass() != this.getClass()) return false;

        Posts p = (Posts) o;
        return (this.idPost == p.getIdPost() && this.idAutor == p.getIdAutor() && this.titulo.equals(p.getTitulo()) &&
                this.data.equals(p.getData()) && this.postType == p.getPostType() && this.idPai == p.getIdPai() && this.comentarios == p.getComentarios() &&
                this.respostas == p.getRespostas() && this.votos == p.getVotos() && this.tags.equals(p.getTags()));
    }

    /**
     * Devolve representação textual do post
     */
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("---Post---");
        sb.append("\nID: ").append(this.idPost);
        sb.append("\nID do Autor: ").append(this.idAutor);
        sb.append("\nTitulo: ").append(this.titulo);
        sb.append("\nData: ").append(this.data);
        sb.append("\nTipo: ").append(this.postType);
        sb.append("\nID da Pergunta: ").append(this.idPai);
        sb.append("\nNumero de Comentarios: ").append(this.comentarios);
        sb.append("\nNumero de Respostas: ").append(this.respostas);
        sb.append("\nNumero de Votos: ").append(this.votos);
        sb.append("\nTags: ").append(this.tags.toString());
        return sb.toString();
    }


    /**
     * Método que insere um post no utilizador a quem pertence tal post
     */
    public void inserePostDoUser(HashMap<Long, Users> tab){

        Set<Posts> posts = tab.get(this.idAutor).getPostsUser();
        if(posts.isEmpty()) {
            Set<Posts> novo = new TreeSet<>(new ComparadorDataPost());
            novo.add(this);
            tab.get(this.idAutor).setPostsUser(novo);
        }
        else {
            posts.add(this);
            tab.get(this.idAutor).setPostsUser(posts);
        }

    }
}

