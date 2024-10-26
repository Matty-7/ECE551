#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

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
