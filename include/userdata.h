#ifndef __USERDATA__
#define __USERDATA__

#include "topN.h"
#include "data.h"
#include "pair.h"
#include "glib.c"
#include "common.h"
#include "listaposts.h"
#include <stdlib.h>

typedef struct user_dataTop* UserDataTop;
typedef struct user_dataPar* UserDataPar;
typedef struct user_dataTitle* UserDataTitle;
typedef struct user_dataRes* UserDataRes;

UserDataTop createUserDataTop(Date i, Date f, ArrayTop t);
Date getDataInicio(UserDataTop d);
Date getDataFim(UserDataTop d);
ArrayTop getArray(UserDataTop d);
void setArray(UserDataTop d);
void freeUserData(UserDataTop d);
UserDataPar createUserDataPar (Date i, Date f,  LONG_pair par);
Date getDataInicioPar(UserDataPar d);
Date getDataFimPar(UserDataPar d);
LONG_pair getPar(UserDataPar d);
void freeUserDataPar(UserDataPar d);
UserDataTitle createUserDataTitle (char* pal, Lista l);
char* getPal (UserDataTitle d);
Lista getListaU (UserDataTitle d);
void setListaU (UserDataTitle d, Lista l)
void freeUserDataTitle(UserDataTitle d);
UserDataRes createUserDataRes (Data i, int rep, long id, int r, TopN t);
Data getDataPergunta (UserDataRes u);
int getRepU (UserDataRes u);
long getIdPergunta (UserDataRes u);
int getAnswersRes (UserDataRes u);
void setAnswers (UserDataRes u, int r);
TopN getTopU (UserDataRes u);
void setTopU (UserDataRes u, TopN n);
void freeUserDataRes(UserDataRes u);

#endif