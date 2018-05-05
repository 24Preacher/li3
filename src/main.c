#include <date.h>
#include <stdio.h>
#include "interface.h"



int main(){

  TAD_community novo = init();
  printf("Correu tudo bem com a init\n");
  novo = load(novo, NULL);

  printf("Fez o load\n");
  info_from_post(novo, 1);
  //total_posts(novo,createDate(01,11,2013),createDate(30,11,2017));

  return 0;
}
