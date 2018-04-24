#include "glib.c"
#include <glib.h>
#include "common.c"
#include "hashtags.h"


typedef struct htags{
    char *tagname;
    long id;
};


HashTags createHashTag(char *tagname, long id){
  Tag t =g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);
  return t;
}



char* getTagName (HashTags t){
	return mystrdup(t->tagname);
}

long getIDTag(HashTags t){
  return (t->id);
}


void freeHashTag (HashTags t){
	 g_hash_table_remove_all(t);
}
