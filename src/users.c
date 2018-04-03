#include "struct.h"
#include <glib.h>
#include "date.c"


struct users
{
	long id_user;
	char* nome;
	char* bio;
	int rep;
	struct users *prox;
}Users;

// tenho de por as cenas de hash aqui ???
Users createUsers (long id, char* nome, char* bio, int rep){
	Users u = malloc (sizeof(struct users));
	u->id_user = id;
	u->nome = mystrdup(nome);
	u->bio = mystrdup(bio);
	u->rep = rep;

	return u;
}


long getUserId (Users u){
	return u->id_user;
}

char* getName (Users u){
	return u->nome;
}

char* getBio (Users u){
	return u->bio;
}

int getRep (Users u){
	return u->rep;
}


void freeUsers (Users u){
	if (u){
		free(u);
	}
