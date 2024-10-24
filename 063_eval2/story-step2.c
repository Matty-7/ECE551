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

void readCategories(const char * filename, catarray_t * categories) {
  FILE * file = fopen(filename, "r");
  if (file == NULL) {
    perror("Error: There is something wrong when trying to open the file");
    exit(EXIT_FAILURE);
  }

  char * line = NULL;
  size_t len = 0;
  ssize_t read;

  while ((read = getline(&line, &len, file)) != -1) {
    char * colon = strchr(line, ':');
    if (colon == NULL) {
      fprintf(stderr, "Error: There is no colon in this line: %s\n", line);
      exit(EXIT_FAILURE);
    }

    *colon = '\0';
    char * category = line;
    char * word = colon + 1;

    // Here we need to remove the new line character from the word
    char * newline = strchr(word, '\n');
    if (newline != NULL) {
      *newline = '\0';
    }

    addWordToCategory(categories, category, word);
  }

  free(line);
  fclose(file);
}

void freeCategories(catarray_t * categories) {
  for (size_t i = 0; i < categories->n; i++) {
    free(categories->arr[i].name);
    for (size_t j = 0; j < categories->arr[i].n_words; j++) {
      free(categories->arr[i].words[j]);
    }
    free(categories->arr[i].words);
  }
  free(categories->arr);
}

int main(int argc, char * argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Here we use: %s <categories_file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  catarray_t categories = {NULL, 0};
  readCategories(argv[1], &categories);

  printWords(&categories);
  freeCategories(&categories);
  return EXIT_SUCCESS;
}
