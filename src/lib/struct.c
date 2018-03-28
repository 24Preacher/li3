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
	char* tag;// array de strings
	int votes_up;
	int votes_down;
	int num_comentarios;
	struct Posts_data *esq, *dir;
};

//Posts ordenados pelo id, considerar outras estruturas
struct Posts_id
{
	long id_post;
	long id_user;
	char* titulo;
	struct Posts_id *esq, *dir;

};

struct Users
{
	long id_user;
	char* nome;
	char* bio;
	int rep;
	long* ult_10posts;
	Users *prox;

};
