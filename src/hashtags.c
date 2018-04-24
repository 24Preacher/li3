#include "glib.c"
#include <glib.h>
#include "common.c"
#include "hashtags.h"


typedef struct htags{
    char *tagname;
    long id;
};


TagHash createHashTag(char *tagname, long id){
  Tag t =g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);
  return t;
}



char* getTagName (TagHash t){
	return mystrdup(t->tagname);
}

long getIDTag(TagHash t){
  return (t->id);
}


void freeTagHash (TagHash t){
	 if (t)
	 	free(t);
}
