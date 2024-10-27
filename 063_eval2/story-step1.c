#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char * argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Here we use: %s <story_template_file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  readStoryTemplate(argv[1]);

  return EXIT_SUCCESS;
}
