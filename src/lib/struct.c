#include "struct.h"
#include <glib.h>
#include "date.c"
#include "user.c"


//POSTS ORDENADOS PELA DATA
struct Posts_data
{
	Date data_post;
	long id_user;
	long id_post;
	char* titulo;
	int num_respostas;
	int post_type; //1 - pergunta, 2 - resposta
	long parent_id; //NULL se for uma pergunta
	//int votes_up; //votetypeid 2
	//int votes_down;//votetypeid 3
	int votos;
	int num_comentarios;
	int score;
	Tags tags;
	struct Posts_data *esq, *dir;
}Posts_D;

// Lista ligada para guardar as tags
struct tags {
	char* nome;
	long id_tag;
	int count;
	struct tags *prox;
} Tags;

//Posts ordenados pelo id, considerar outras estruturas
struct Posts_id
{
	long id_post;
	long id_user;
	char* titulo;
	Date data;
	struct Posts_id *esq, *dir;
}Posts_ID;

struct users
{
	long id_user;
	char* nome;
	char* bio;
	int rep;
	Users *prox;
}Users;
