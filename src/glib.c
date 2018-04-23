#include <glib.h>
#include "data.h"
#include "date.h"
#include "postsID.h"
#include "postsD.h"




int compareData(Data a, Data b){

    if (getAno(a) > getAno(a)) return 1;
    else if (getAno(a) < getAno(b)) return -1;
    else if (getMes(a) > getMes(b)) return 1;
    else if (getMes(a) < getMes(b)) return -1;
    else if (getDia(a) > getDia(b)) return 1;
    else if (getDia(a) < getDia(b)) return -1;
    else if (getHora(a) > getHora(b)) return 1;
    else if (getHora(a) < getHora(b)) return -1;
    else if (getMinutos(a) > getMinutos(b)) return 1;
    else if (getMinutos(a) < getMinutos(b)) return -1;
    else return 0;

}

//Compara datas dos stores com as nossas
int compareDate(Date a, Date b){
    if

}


Date converteData(Data a){
  Date d = createDate(a->dia, a->mes, a->ano);
  return d;
}

int dataIgual(Date a, Data b){
  b = converteData(b);

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
