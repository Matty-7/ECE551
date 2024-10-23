#include "IntArray.h"

#include <assert.h>

#include <ostream>

IntArray::IntArray() {
  data = NULL;
  numElements = 0;
}
IntArray::IntArray(int n) {
  numElements = n;
  data = new int[n];

  for (int i = 0; i < numElements; i++) {
    data[i] = 0;
  }
}

IntArray::IntArray(const IntArray & rhs) {
  numElements = rhs.numElements;
  data = new int[numElements];

  for (int i = 0; i < numElements; i++) {
    data[i] = rhs.data[i];
  }
}
IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs) {
    delete[] data;
    numElements = rhs.numElements;
    data = new int[numElements];

    for (int i = 0; i < numElements; i++) {
      data[i] = rhs.data[i];
    }
  }
  return *this;
}

const int & IntArray::operator[](int index) const {
  assert(index >= 0 && index < numElements);
  return data[index];
}

int & IntArray::operator[](int index) {
  assert(index >= 0 && index < numElements);
  return data[index];
}

int IntArray::size() const {
  return numElements;
}

IntArray IntArray::operator+(const IntArray & rhs) const {
  assert(numElements == rhs.numElements);
  IntArray result(numElements);
  for (int i = 0; i < numElements; i++) {
    result[i] = (*this)[i] + rhs[i];
  }
  return result;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if (numElements != rhs.numElements) {
    return false;
  }

  for (int i = 0; i < numElements; i++) {
    if (data[i] != rhs.data[i]) {
      return false;
    }
  }
  return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  return !(*this == rhs);
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  s << "{";
  for (int i = 0; i < rhs.size(); i++) {
    s << rhs[i];
    if (i < rhs.size() - 1) {
      s << ", ";
    }
  }
  s << "}";
  return s;
}