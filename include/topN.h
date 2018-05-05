#ifndef __TOPN__
#define __TOPN__

#include <stdlib.h>
#include "data.h"


typedef struct topn* TopN;
typedef struct topArray* ArrayTop;
typedef struct auxdata* AuxData;
typedef struct arraydata* ArrayData;

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
void insereResTop(ArrayTop t, TopN n);
void alteraCount(ArrayTop t, long id);
AuxData createAuxData(Data d, long p);
Data getData_Aux (AuxData c);
long getId_Aux (AuxData c);
void freeAuxData(AuxData c);
ArrayData createArrayData (int size);
int getSizeArrayData (ArrayData c);
int getOcupadosData (ArrayData c);
void setOcupadosData (ArrayData c, int o);
AuxData getAuxData (ArrayData c, int i);
void setAuxData (ArrayData c, AuxData nova, int i);
void freeArrayData (ArrayData c);
void inserePelaData(ArrayData c, AuxData nova);
AuxData cloneAuxData(AuxData c);
ArrayData cloneArrayData(ArrayData c);

#endif
