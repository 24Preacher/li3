#include "users.h"
#include "common.c"
#include "glib.c"
#include <glib.h>

/**
\struct Estrutura(Tabela de Hash com chaining) que armazena os utilizadores
@param id_user Identificador do utilizador
@param nome    Nome do utilizador
@param bio     Descrição do utilizador
@param rep 		 Reputação do utilizador
*/
struct users
{
	long id_user;
	char* nome;
	char* bio;
	int rep;
}Users;

/**
\brief Função que cria a estrutura de utilizadores
@param id_user Identificador do utilizador
@param nome    Nome do utilizador
@param bio     Descrição do utilizador
@param rep 		 Reputação do utilizador
returns A estrutura de utilizadores
*/
Users createUsers (long id, char* nome, char* bio, int rep){

	int h = g_direct_hash(id)
	Users *novo = g_hash_table_new(GHashFunc g_direct_hash(id),GEqualFunc g_direct_equal(id,novo[h]->id_user));
// acho que so verifica a primeira celula na posiçao h da tabela
	return novo;
}

/**
\brief Função que busca o identificador do utilizador
@param Estrutura dos utilizadores
@returns O id do post
*/

long getUserId (Users u){
	return u->id_user;
}

/**
\brief Função que busca o nome do utilizador
@param Estrutura dos utilizadores
@returns Apontador para o nome do utilizador
*/
char* getName (Users u){
	return mystrdup(u->nome);
}

/**
\brief Função que busca a descrição do utilizador
@param Estrutura dos utilizadores
@returns Apontador para a bio do utilizador
*/
char* getBio (Users u){
	return mystrdup(u->bio);
}

/**
\brief Função que busca a reputação do utilizador
@param Estrutura dos utilizadores
@returns A reputação do utilizador
*/
int getRep (Users u){
	return u->rep;
}

/**
\brief Função que liberta a estrutura dos utilizadores
@param Estrutura dos utilizadores
*/
void freeUsers (Users u){
	if (u){
		free(u->prox);
		free(u);
	}
