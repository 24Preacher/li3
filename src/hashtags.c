#include "hashtags.h"


struct htags{
    char *tagname;
    long id;
};


HashTags createHashTag(char *tagname, long id){
  HashTags t = malloc(sizeof(struct htags));
  t->tagname = mystrdup(tagname);
  t->id = id;
  return t;
}



char* getTagName (HashTags t){
	return mystrdup(t->tagname);
}

long getIDTag(HashTags t){
  return (t->id);
}


void freeHashTag (gpointer t){
	 g_hash_table_remove_all((GHashTable*) t);
}
