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
}Posts_D;

Posts_D createPostsD (Data d, long user, long post, char* title,int respostas,
		short ptype, long parent, int votes, int com, int score, Tags t){
			Posts_D *r = g_tree_new((GCompareFunc)r->data_post);//criar func??

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

char* getTitle (Posts_ID posts){
	return mystrdup(posts->titulo);
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
