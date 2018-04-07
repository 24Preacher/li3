#include <date.h>
#include <stdio.h>
#include "parser.c"

int main(){
  Date d = createDate(1,2,2017);
  printf("Dia: %i\n", get_day(d));
  return 0;
}
