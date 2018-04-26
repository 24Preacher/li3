#ifndef __TOPN__
#define __TOPN__

#include <stdlib.h>


typedef struct topn* TopN;
typedef struct topArray* ArrayTop;

TopN createTopN (long id, int c);
int getID_Top(TopN t);
int getCount(TopN t);
void setCount(TopN t, int c);
void freeTop (TopN t);
ArrayTop createArrayTop (int size);
int getSizeTop (ArrayTop t);
int getOcupados2(ArrayTop t);
void setOcupados2(ArrayTop t, int o);
TopN getTop (ArrayTop t ,int i);
void setTop(ArrayTop t, TopN n, int i);
void freeArrayTop(ArrayTop t);
void insereTop (ArrayTop t, TopN n);
TopN cloneTopN(TopN t);
ArrayTop cloneArrayTop(ArrayTop t);

#endif
