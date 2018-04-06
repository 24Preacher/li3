#include "postsD.h"
#include "data.c"
#include <glib.h>
#include <stdlib.h>


//POSTS ORDENADOS PELA DATA
struct Posts_data
{
	Data data_post;
	long id_user;
	long id_post;
	char* titulo;
	int num_respostas;
	short post_type; //1 - pergunta, 2 - resposta
	long parent_id;
	int votos;
	int num_comentarios;
	int score;
	Tags tags;
	struct Posts_data *esq, *dir;
}Posts_D;

Posts_D createPostsD (Data d, long user, long post, char* title,int respostas,
		short ptype, long parent, int votes, int com, int score, Tags t){
			Posts_D *r = g_tree_new((GCompareFunc)r->data_post);//criar func??

			g_tree_insert(r, r->data_post, d);
			g_tree_insert(r, r->id_user, user);
			g_tree_insert(r, r->id_post, post);
			g_tree_insert(r, r->titulo, title);
			g_tree_insert(r, r->num_respostas, respostas;
			g_tree_insert(r, r->post_type, ptype);
			g_tree_insert(r, r->parent_id, parent);
			g_tree_insert(r, r->votos, votes);
			g_tree_insert(r, r->num_comentarios, com);
			g_tree_insert(r, r->score, score);
			g_tree_insert(r, r->tags, t);
			g_tree_insert(r, r->esq, NULL);
			g_tree_insert(r, r->dir, NULL);

			return r;
	}


Date getDate (Posts_D posts){
	return posts->data_post;
}

long getUserId (Posts_D posts){
	return posts->id_user;
}

long getPostId (Posts_D posts){
	return posts->id_post;
}

char* getTitle (Posts_D posts){
	return posts->titulo;
}

int getAnswers (Posts_D posts){
	return posts->num_respostas;
}

short getPostType (Posts_D posts){
	return posts->post_type;
}

long getParentId (Posts_D posts){
	return posts->parent_id;
}

int getVotes (Posts_D posts){
	return posts->votos;
}

int getComments (Posts_D posts){
	return posts->num_comentarios;
}

int getScore (Posts_D posts){
	return posts->score;
}
// fazer mais alguma cena adicional pq é um lista de strings??
Tags getTags (Posts_D posts){
	return posts->tags;
}
