#include <date.h>
#include <stdio.h>
#include "interface.h"
// #include "time.h"
#include "pair.h"



int main(){
//   clock_t tempo;
//   tempo = clock();
  
  TAD_community novo = init();
  printf("Correu tudo bem com a init\n");
  novo = load(novo, NULL);

//   tempo = clock() - tempo;
//   printf("Load demorou %f segundos\n", ((float)tempo/CLOCKS_PER_SEC));
  printf("Fez o load\n");
  
  return 0;
}
