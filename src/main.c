#include <date.h>
#include <stdio.h>
#include "interface.h"



int main(){
    
  TAD_community novo = init();
  printf("Correu tudo bem com a init\n");
  novo = load(novo, NULL);

  printf("Fez o load\n");
  info_from_post(novo, 1);

  return 0;
}
