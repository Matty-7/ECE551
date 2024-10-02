#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 10
#define COLS 10
#define TOTAL_SIZE 110

int main(int argc, char ** argv) {
  char matrix[ROWS][COLS];
  char char_buffer[TOTAL_SIZE];
  int c;
  int index = 0;

  if (argc != 2) {
    fprintf(stderr, "error\n");
    return EXIT_FAILURE;
  }

  FILE * file = fopen(argv[1], "r");
  if (file == NULL) {
    fprintf(stderr, "error\n");
    return EXIT_FAILURE;
  }

  while ((c = fgetc(file)) != EOF) {
    if (index >= TOTAL_SIZE) {
      fprintf(stderr, "error\n");
      fclose(file);
      return EXIT_FAILURE;
    }
    if (c >= 128) {
      fprintf(stderr, "error\n");
      fclose(file);
      return EXIT_FAILURE;
    }
    if (c == '\n' && index % (COLS + 1) != COLS) {
      fprintf(stderr, "error\n");
      fclose(file);
      return EXIT_FAILURE;
    }
    if (c != '\n' && index % (COLS + 1) == COLS) {
      fprintf(stderr, "error\n");
      fclose(file);
      return EXIT_FAILURE;
    }
    char_buffer[index] = c;
    index++;
  }

  if (index != TOTAL_SIZE) {
    fprintf(stderr, "error\n");
    fclose(file);
    return EXIT_FAILURE;
  }

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      matrix[j][ROWS - 1 - i] = char_buffer[i * (COLS + 1) + j];
    }
  }

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      fprintf(stdout, "%c", matrix[i][j]);
    }
    fprintf(stdout, "\n");
  }

  if (fclose(file) != 0) {
    fprintf(stderr, "error\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
