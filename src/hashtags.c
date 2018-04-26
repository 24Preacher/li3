#include "hashtags.h"


struct htags{
    char *tagname;
    long id;
};


GHashTable* createHashTag(char *tagname, long id){
  GHashTable* t = g_hash_table_new_full(g_str_hash, g_str_equal, free,  (GDestroyNotify) freeHashTag);
  return t;
}



char* getTagName (HashTags t){
	return mystrdup(t->tagname);
}

long getIDTag(HashTags t){
  return (t->id);
}


void freeHashTag (HashTags t){
	 g_hash_table_remove_all((GHashTable*) t);
}
