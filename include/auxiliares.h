#ifndef __AUXILIARES__
#define __AUXILIARES__



#include "data.h"
#include "date.h"
#include "userdata.h"
#include "listaposts.h"
#include "parser.h"
#include "postsD.h"
#include "postsID.h"
#include "tags.h"
#include "users.h"
#include "string.h"
#include <glib.h>
#include "topN.h"
#include "list.h"

LONG_list converteTopList(ArrayTop t, int N);
void percorre(ArrayPosts p, ArrayTop t);
gboolean incrementaPar (Posts_D p, UserDataPar u);
gboolean checkTags(Posts_D p, UserDataTag u);
gboolean topScore(Posts_D p, UserDataTop top);
gboolean inserePerguntas(Posts_D p, UserDataTop top);
gboolean incrementaRespostas(Posts_D p, UserDataTop top);
int pertenceTitulo(char* palavra, Posts_D p);
gboolean temPalavra(Posts_D p, UserDataTitle u);
int valResposta(Posts_D p, int rep);
gboolean melhor(Posts_D p, UserDataRes u);

#endif
