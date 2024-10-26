#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"

//any functions you want your main to use

void readCategories(const char * filename, catarray_t * categories);
void freeCategories(catarray_t * categorries);
void addWordToCategory(catarray_t * categories, const char * category, const char * word);

#endif
