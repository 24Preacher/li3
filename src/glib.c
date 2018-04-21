#include <glib.h>
#include "data.h"
#include "date.h"
#include "PostsID.h"




int compareData(Data a, Data b){

    if(a->ano > b->ano) return 1;
    else if (a->ano < b->ano) return -1;
    else if (a->mes > b->mes) return 1;
    else (a->mes < b->mes) return -1;
    else (a->dia > b->dia) return 1;
    else (a->dia < b->dia) return -1;
    else (a->hora > b->hora) return 1;
    else (a->hora < b->hora) return -1;
    else (a->min > b->min) return 1;
    else (a->min < b->min) return -1
    else return 0;

}

//Compara datas dos stores com as nossas
int dataIgual(Date a, Data b){
    if(a->ano > b->ano) return 1;
    else if (a->ano < b->ano) return -1;
    else if (a->mes > b->mes) return 1;
    else (a->mes < b->mes) return -1;
    else (a->dia > b->dia) return 1;
    else (a->dia < b->dia) return -1;
    else return 0;
}

int data_ord (Posts_D a, Posts_D b){
  return (compareData(a->data_post, b->data_post));
}

int compareID(Posts_ID a, Posts_ID b){
    if(a->id_user > b->id_user)
        return 1;
    else if (a->id_user < b->id_user)
        return -1;
    else return 0;
}
