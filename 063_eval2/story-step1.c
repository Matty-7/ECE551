#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

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

int main(int argc, char * argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <story_template_file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  readStoryTemplate(argv[1]);

  return EXIT_SUCCESS;
}
