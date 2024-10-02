#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26

void count_letter_frequency(FILE * file, int letter_count[]) {
  char c;
  while ((c = fgetc(file)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      letter_count[c - 'a']++;
    }
  }
}

int find_most_frequent_letter(int letter_count[]) {
  int max_count = 0;
  int most_frequent_letter = 0;

  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if (letter_count[i] > max_count) {
      max_count = letter_count[i];
      most_frequent_letter = i;
    }
  }
  return most_frequent_letter;
}

int main(int argc, char * argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return EXIT_FAILURE;
  }

  FILE * file = fopen(argv[1], "r");
  if (!file) {
    perror("Error opening file");
    return EXIT_FAILURE;
  }

  int letter_count[ALPHABET_SIZE] = {0};

  count_letter_frequency(file, letter_count);
  fclose(file);

  int most_frequent_letter = find_most_frequent_letter(letter_count);

  int key = (most_frequent_letter - ('e' - 'a') + ALPHABET_SIZE) % ALPHABET_SIZE;

  printf("%d\n", key);
  return EXIT_SUCCESS;
}
