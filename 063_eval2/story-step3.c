#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char * argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Here we use %s <categories_file> <story_template_file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  catarray_t categories = {NULL, 0};
  readCategories(argv[1], &categories);

  processStoryTemplate(argv[2], &categories, 0);

  freeCategories(&categories);

  return EXIT_SUCCESS;
}
