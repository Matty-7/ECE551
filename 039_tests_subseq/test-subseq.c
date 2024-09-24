#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void run_test(int * array, size_t n, size_t expected) {
  size_t result = maxSeq(array, n);
  if (result == expected) {
    printf("Test passed.\n");
  }
  else {
    printf("Test failed. Expected %zu but got %zu.\n", expected, result);
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  run_test(NULL, 0, 0);

  int array1[] = {42};
  run_test(array1, 1, 1);

  int array2[] = {1, 1, 1, 1, 1};
  run_test(array2, 5, 1);

  int array3[] = {1, 2, 3, 4, 5};
  run_test(array3, 5, 5);

  int array4[] = {1, 3, 5, 4, 2, 3, 4, 5, 0, 10};
  run_test(array4, 10, 4);

  int array5[] = {-2, -1, 0, 1, -1, 0, 1, 2};
  run_test(array5, 8, 4);

  int array6[] = {5, 4, 3, 2, 1};
  run_test(array6, 5, 1);

  int array7[] = {1, 2, 3, 4, 5, 4, 3, 2, 1};
  run_test(array7, 9, 5);

  int array8[] = {1, 2, 3, 4, 5, 5};
  run_test(array8, 6, 5);

  printf("All tests passed!\n");
  return EXIT_SUCCESS;
}
