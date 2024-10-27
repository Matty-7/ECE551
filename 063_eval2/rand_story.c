#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Replace the blanks in one line
void processLine(char * line) {
  char * start = line;
  char * end = NULL;

  while ((start = strchr(start, '_')) != NULL) {
    end = strchr(start + 1, '_');
    if (end == NULL) {
      fprintf(stderr, "Error: unmatched underscore in this line: %s\n", line);
      exit(EXIT_FAILURE);
    }

    // Here I print the text before the blank
    *start = '\0';
    printf("%s", line);

    printf("%s", chooseWord(NULL, NULL));

    line = end + 1;
    start = line;
  }

  // Here I print the remaining of the line
  printf("%s", line);
}

void readStoryTemplate(const char * filename) {
  FILE * file = fopen(filename, "r");

  if (file == NULL) {
    perror("There is an error when trying to open the file");
    exit(EXIT_FAILURE);
  }

  char * line = NULL;
  size_t len = 0;
  ssize_t read;

  // Read each line from the input file
  while ((read = getline(&line, &len, file)) != -1) {
    processLine(line);
  }

  free(line);
  fclose(file);
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

void removeWordFromCategory(catarray_t * categories,
                            const char * category,
                            const char * word) {
  for (size_t i = 0; i < categories->n; i++) {
    if (strcmp(categories->arr[i].name, category) == 0) {
      // First we need to find the word in the category
      for (size_t j = 0; j < categories->arr[i].n_words; j++) {
        if (strcmp(categories->arr[i].words[j], word) == 0) {
          // Then we need to free the word and shift the remaining words
          free(categories->arr[i].words[j]);
          for (size_t k = j; k < categories->arr[i].n_words - 1; k++) {
            categories->arr[i].words[k] = categories->arr[i].words[k + 1];
          }
          categories->arr[i].n_words--;
          categories->arr[i].words =
              realloc(categories->arr[i].words,
                      categories->arr[i].n_words * sizeof(*categories->arr[i].words));
          if (categories->arr[i].n_words > 0 && categories->arr[i].words == NULL) {
            perror("Error: Reallocating memory has problem");
            exit(EXIT_FAILURE);
          }
          return;
        }
      }
    }
  }
  fprintf(stderr, "Error: Word '%s' was not in category '%s'\n", word, category);
  exit(EXIT_FAILURE);
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

// Here I put the used word in a list of used words
void addUsedWord(char *** usedWords, size_t * n_used, const char * word) {
  *usedWords = realloc(*usedWords, (*n_used + 1) * sizeof(**usedWords));
  (*usedWords)[*n_used] = strdup(word);
  (*n_used)++;
}

// It can return the used word in the used word list
const char * getUsedWord(char ** usedWords, size_t n_used, int index) {
  if (index <= 0 || index > n_used) {
    fprintf(stderr, "Error: The index input is invalid\n");
    exit(EXIT_FAILURE);
  }
  return usedWords[n_used - index];
}

void processStoryTemplate(const char * filename, catarray_t * categories, int noReuse) {
  FILE * file = fopen(filename, "r");
  if (file == NULL) {
    perror("Error: Can't open the file");
    exit(EXIT_FAILURE);
  }

  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  char ** usedWords = NULL;
  size_t n_used = 0;

  while ((read = getline(&line, &len, file)) != -1) {
    char * current_position = line;
    char * start = NULL;
    char * end = NULL;

    // Deal with the placeholder in each line
    while ((start = strchr(current_position, '_')) != NULL) {
      end = strchr(start + 1, '_');
      if (end == NULL) {
        fprintf(stderr,
                "Error: There are some unmatched underlines in this line: %s\n",
                line);
        exit(EXIT_FAILURE);
      }

      // We need to print the text before the placeholder
      *start = '\0';
      printf("%s", current_position);

      // We need to get the placeholder content
      *end = '\0';
      char * placeholder = start + 1;

      const char * replacement = NULL;
      char * replacementCopy = NULL;
      char * endptr;
      int index = strtol(placeholder, &endptr, 10);

      if (*endptr == '\0') {
        replacement = getUsedWord(usedWords, n_used, index);
        printf("%s", replacement);
      }
      else {
        replacement = chooseWord(placeholder, categories);
        replacementCopy = strdup(replacement);

        if (noReuse) {
          removeWordFromCategory(categories, placeholder, replacement);
        }

        addUsedWord(&usedWords, &n_used, replacementCopy);

        printf("%s", replacementCopy);
      }

      // Move the placeholder
      current_position = end + 1;
    }

    printf("%s", current_position);
  }

  for (size_t i = 0; i < n_used; i++) {
    free(usedWords[i]);
  }
  free(usedWords);
  free(line);
  fclose(file);
}
