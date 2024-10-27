#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char * argv[]) {
  int noReuse = 0;
  int argIndex = 1;

  if (argc < 3 || argc > 4) {
    fprintf(
        stderr, "Here we use %s [-n] <categories_file> <story_template_file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if (argc == 4) {
    if (strcmp(argv[1], "-n") == 0) {
      noReuse = 1;
      argIndex = 2;
    }
    else {
      fprintf(stderr, "Error: Here is an invalid option: %s\n", argv[1]);
      exit(EXIT_FAILURE);
    }
  }

  catarray_t categories = {NULL, 0};
  readCategories(argv[argIndex], &categories);
  processStoryTemplate(argv[argIndex + 1], &categories, noReuse);
  freeCategories(&categories);

  return EXIT_SUCCESS;
}
