#include <date.h>
#include <stdio.h>
#include "interface.h"
#include "time.h"



int main(){
  clock_t tempo;
tempo = clock();

TAD_community novo = init();
novo = load(novo, NULL);

tempo = clock() - tempo;
printf("Load demorou %f segundos", ((float)tempo/CLOCKS_PER_SEC));

return 0;
}
