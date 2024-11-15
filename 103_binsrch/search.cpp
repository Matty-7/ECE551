#include <cmath>
#include <iostream>

#include "function.h"

using namespace std;

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low >= high) {
    return low;
  }

  while (low + 1 < high) {
    int mid = low + (high - low) / 2;
    int result = f->invoke(mid);

    if (result <= 0) {
      low = mid;
    }
    else {
      high = mid;
    }
  }

  return low;
}
