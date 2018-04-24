#ifndef __USERDATA__
#define __USERDATA__

#include "topN.h"
#include "data.h"

typedef struct user_data* UserData;

UserData createUserData(Data i, Data f, ArrayTop t);
Data getDataInicio(UserData d);
Data getDataFim(UserData d);
ArrayTop getArray(UserData d);
void setArray(UserData d);
void freeUserData(UserData d);

#endif
