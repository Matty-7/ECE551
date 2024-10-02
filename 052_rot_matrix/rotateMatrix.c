#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

void rotate_matrix(char matrix[SIZE][SIZE], char rotated_matrix[SIZE][SIZE]) {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      rotated_matrix[j][SIZE - 1 - i] = matrix[i][j];
    }
  }
}

int main(int argc, char * argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <input file>\n", argv[0]);
    return EXIT_FAILURE;
  }

  FILE * file = fopen(argv[1], "r");
  if (!file) {
    perror("Error opening file");
    return EXIT_FAILURE;
  }

  char matrix[SIZE][SIZE];
  char rotated_matrix[SIZE][SIZE];
  char line[SIZE + 2];

  for (int i = 0; i < SIZE; i++) {
    if (fgets(line, sizeof(line), file) == NULL) {
      fprintf(stderr, "Error reading line %d\n", i + 1);
      fclose(file);
      return EXIT_FAILURE;
    }

    if (line[SIZE] != '\n' || line[SIZE + 1] != '\0') {
      fprintf(stderr, "Invalid line length on line %d\n", i + 1);
      fclose(file);
      return EXIT_FAILURE;
    }

    for (int j = 0; j < SIZE; j++) {
      matrix[i][j] = line[j];
    }
  }

  fclose(file);

  rotate_matrix(matrix, rotated_matrix);

  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      putchar(rotated_matrix[i][j]);
    }
    putchar('\n');
  }

  return EXIT_SUCCESS;
}
