#include <glib.h>
#include "data.h"
#include "date.h"
#include "PostsID.h"




int compareData(Data a, Data b){
    int r;
    
    if(a->ano > b->ano)
        r = 1;
    else if (a->ano < b->ano)
        r = -1;
    else if (a->mes > b->mes)
        r = 1;
    else (a->mes < b->mes)
        r = -1;
    else (a->dia > b->dia)
        r = 1;
    else (a->dia < b->dia)
        r = -1;
    else (a->hora > b->hora)
        r = 1;
    else (a->hora < b->hora)
        r = -1;
    else (a->min > b->min)
        r = 1;
    else (a->min < b->min)
        r = -1;
    else r = 0;
    
    return r;
}

//Compara datas dos stores com as nossas
int dataIgual(Date a, Data b){
    if(a->ano > b->ano)
        r = 1;
    else if (a->ano < b->ano)
        r = -1;
    else if (a->mes > b->mes)
        r = 1;
    else (a->mes < b->mes)
        r = -1;
    else (a->dia > b->dia)
        r = 1;
    else (a->dia < b->dia)
        r = -1;
    
    return r;
}

int data_ord (Posts_D a, Posts_D b){
  return (compareData(a->data_post, b->data_post));
}

int compareID(Posts_ID a, Posts_ID b){
    int r;
    if(a->id_user > b->id_user)
        r = 1;
    else if (a->id_user < b->id_user)
        r = -1;
    else r = 0;
    return r;
}



