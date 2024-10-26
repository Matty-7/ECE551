#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

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

void processStoryTemplate(const char * filename, catarray_t * categories) {
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
    char * start = line;
    char * end = NULL;

    while ((start = strchr(start, '_')) != NULL) {
      end = strchr(start + 1, '_');
      if (end == NULL) {
        fprintf(stderr,
                "Error: There are some unmatched underlines in this line: %s\n",
                line);
        exit(EXIT_FAILURE);
      }

      // We need to print the text before the placeholder
      *start = '\0';
      printf("%s", line);

      // We need to get the placeholder
      *end = '\0';
      char * placeholder = start + 1;

      const char * replacement;
      char * endptr;
      int index = strtol(placeholder, &endptr, 10);
      if (*endptr == '\0') {
        replacement = getUsedWord(usedWords, n_used, index);
      }
      else {
        replacement = chooseWord(placeholder, categories);
        addUsedWord(&usedWords, &n_used, replacement);
      }

      printf("%s", replacement);

      // Move the placeholder
      line = end + 1;
      start = line;
    }

    printf("%s", line);
  }

  for (size_t i = 0; i < n_used; i++) {
    free(usedWords[i]);
  }
  free(usedWords);
  free(line);
  fclose(file);
}

int main(int argc, char * argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Here we use %s <categories_file> <story_template_file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  catarray_t categories = {NULL, 0};
  readCategories(argv[1], &categories);

  processStoryTemplate(argv[2], &categories);

  freeCategories(&categories);

  return EXIT_SUCCESS;
}
