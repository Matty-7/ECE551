#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

int read_lines(FILE * f, char *** data, size_t * count) {
  char * line = NULL;
  size_t len = 0;
  ssize_t nread;
  size_t capacity = 10;
  *data = malloc(capacity * sizeof(char *));

  if (*data == NULL) {
    return -1;
  }

  while ((nread = getline(&line, &len, f)) != -1) {
    if (*count >= capacity) {
      capacity *= 2;
      *data = realloc(*data, capacity * sizeof(char *));
      if (*data == NULL) {
        free(line);
        return -1;
      }
    }
    (*data)[*count] = strdup(line);
    if ((*data)[*count] == NULL) {
      free(line);
      return -1;
    }
    (*count)++;
  }
  free(line);
  return 0;
}

void process_stdin() {
  char ** data = NULL;
  size_t count = 0;

  if (read_lines(stdin, &data, &count) != 0) {
    fprintf(stderr, "Error reading from stdin\n");
    exit(EXIT_FAILURE);
  }

  sortData(data, count);

  for (size_t i = 0; i < count; i++) {
    printf("%s", data[i]);
    free(data[i]);
  }
  free(data);
}

void process_file(const char * filename) {
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Error opening file: %s\n", filename);
    exit(EXIT_FAILURE);
  }

  char ** data = NULL;
  size_t count = 0;

  if (read_lines(f, &data, &count) != 0) {
    fprintf(stderr, "Error reading file: %s\n", filename);
    fclose(f);
    exit(EXIT_FAILURE);
  }

  sortData(data, count);

  for (size_t i = 0; i < count; i++) {
    printf("%s", data[i]);
    free(data[i]);
  }

  free(data);
  fclose(f);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    process_stdin();
  }
  else {
    for (int i = 1; i < argc; i++) {
      process_file(argv[i]);
    }
  }

  return EXIT_SUCCESS;
}
