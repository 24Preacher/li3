
#ifndef HASHTAGS_H
#define HASHTAGS_H


typedef struct htags* HashTags;

HashTags createHashTag(char *tagname, long id);
char* getTagName (HashTags t);
long getIDTag(HashTags t);
void freeTagHash (HashTags t);

#endif
