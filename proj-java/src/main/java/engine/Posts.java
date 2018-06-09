package engine;


import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.time.LocalDateTime;

public class Posts {
    private long idPost;
    private long idAutor;
    private String titulo;
    private LocalDateTime data;
    private int postType;
    private long idPai;
    private int comentarios;
    private int respostas;
    private int votos;
    private List<String> tags;

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

    //GETS

    public long getIdPost(){
        return this.idPost;
    }

    public long getIdAutor(){
        return this.idAutor;
    }

    public String getTitulo(){
        return this.titulo;
    }

    public LocalDateTime getData(){
        return this.data;
    }

    public int getPostType(){
        return this.postType;
    }

    public long getIdPai(){
        return this.idPai;
    }

    public int getComentarios(){
        return this.comentarios;
    }

    public int getRespostas(){
        return this.respostas;
    }

    public int getVotos(){
        return this.votos;
    }

    public List<String> getTags(){
        List<String> res = new ArrayList<>();

        for(String s : this.tags)
            res.add(s);
        return res;
    }

    //SETS

    public void setIdPost(long post){
        this.idPost = post;
    }

    public void setIdAutor(long user){
        this.idAutor = user;
    }

    public void setTitulo(String title){
        this.titulo = title;
    }

    public void setData(LocalDateTime d){
        this.data = d;
    }

    public void setPostType(int type){
        this.postType = type;
    }

    public void setIdPai(long pai){
        this.idPai = pai;
    }

    public void setComentarios(int com){
        this.comentarios = com;
    }

    public void setRespostas(int res){
        this.respostas = res;
    }

    public void setVotos(int votos){
        this.votos = votos;
    }

    public void setTags(List<String> novasTags){
        this.tags = new ArrayList<>();
        for(String s : novasTags)
            this.tags.add(s);
    }

    //CLONE

    public Posts clone(){
        return new Posts(this);
    }

    //EQUALS

    public boolean equals(Object o){
        if(o == this) return true;
        if(o == null || o.getClass() != this.getClass()) return false;

        Posts p = (Posts) o;
        return (this.idPost == p.getIdPost() && this.idAutor == p.getIdAutor() && this.titulo.equals(p.getTitulo()) &&
                this.data.equals(p.getData()) && this.postType == p.getPostType() && this.idPai == p.getIdPai() && this.comentarios == p.getComentarios() &&
                this.respostas == p.getRespostas() && this.votos == p.getVotos() && this.tags.equals(p.getTags()));
    }

    //ToString
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

    //insere um post nos user a que pertence

    public void inserePostDoUser(HashMap<Long, Users> tab){
        tab.get(this.idAutor).getPostsUser().add(this);
    }
}

