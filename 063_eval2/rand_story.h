#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"

//any functions you want your main to use

void processLine(char * line);
void readStoryTemplate(const char * filename);
void processStoryTemplate(const char * filename, catarray_t * categories, int noReuse);
void readCategories(const char * filename, catarray_t * categories);
void freeCategories(catarray_t * categorries);
void addWordToCategory(catarray_t * categories, const char * category, const char * word);
void removeWordFromCategory(catarray_t * categories,
                            const char * category,
                            const char * word);
void addUsedWord(char *** usedWords, size_t * n_used, const char * word);

const char * getUsedWord(char ** usedWords, size_t n_used, int index);

#endif
