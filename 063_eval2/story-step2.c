#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

void addWordToCategory(catarray_t * categories,
                       const char * category,
                       const char * word) {
  // Here I check if the category exitst, if so, we add the words in the existing category
  for (size_t i = 0; i < categories->n; i++) {
    if (strcmp(categories->arr[i].name, category) == 0) {
      categories->arr[i].words =
          realloc(categories->arr[i].words,
                  (categories->arr[i].n_words + 1) * sizeof(*categories->arr[i].words));
      categories->arr[i].words[categories->arr[i].n_words] = strdup(word);
      categories->arr[i].n_words++;
      return;
    }
  }

  // Here we create a category if it does not exist yet
  categories->arr =
      realloc(categories->arr, (categories->n + 1) * sizeof(*categories->arr));
  categories->arr[categories->n].name = strdup(category);
  categories->arr[categories->n].words =
      malloc(sizeof(*categories->arr[categories->n].words));
  categories->arr[categories->n].words[0] = strdup(word);
  categories->arr[categories->n].n_words = 1;
  categories->n++;
}
