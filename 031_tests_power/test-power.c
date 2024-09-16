#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);
void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned ans = power(x, y);
  if (ans != expected_ans) {
    exit(EXIT_FAILURE);
  }
}

int main() {
  run_check(0, 0, 1);
  run_check(2, 2, 4);
  run_check(2, 3, 8);
  run_check(4294967295, 1, 4294967295);
  run_check(1, 0, 1);
  run_check(1, 100, 1);
  run_check(0, 1, 0);

  return EXIT_SUCCESS;
}
