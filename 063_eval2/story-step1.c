#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    printf("%s", line);
  }

  free(line);
  fclose(file);
}

int main(int argc, char * argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <story_template_file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  readStoryTemplate(argv[1]);

  return EXIT_SUCCESS;
}
