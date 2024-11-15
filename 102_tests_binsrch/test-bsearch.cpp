#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "function.h"

using namespace std;

extern int binarySearchForZero(Function<int, int> * f, int low, int high);

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n), f(fn), mesg(m) {}

  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }

    remaining--;
    return f->invoke(arg);
  }
};

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  unsigned max_calls = (high > low) ? log2(high - low) + 1 : 1;

  CountedIntFn counted_fn(max_calls, f, mesg);

  int result = binarySearchForZero(&counted_fn, low, high);

  if (result != expected_ans) {
    cerr << "Test failed for: " << mesg << ". Expected: " << expected_ans
         << ", but got: " << result << endl;
    exit(EXIT_FAILURE);
  }
}

class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class LinearFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg; }
};

int main() {
  SinFunction sin_func;
  LinearFunction linear_func;

  check(&sin_func, 0, 150000, 52359, "SinFunction");
  check(&linear_func, 1, 2, 1, "LinearFunction");
  check(&linear_func, -2, 0, -1, "LinearFunction");
  check(&linear_func, -2, -1, -2, "LinearFunction");
  check(&linear_func, 0, 2, 0, "LinearFunction");
  check(&linear_func, -1, 3, 0, "LinearFunction");
  check(&linear_func, 1, 1, 1, "LinearFunction");

  cout << "All tests passed successfully!" << endl;
  return EXIT_SUCCESS;
}
