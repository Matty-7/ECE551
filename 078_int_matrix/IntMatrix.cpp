#include "IntMatrix.h"

#include <cassert>
#include <iostream>

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {
}

IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c) {
  rows = new IntArray *[numRows];

  for (int i = 0; i < numRows; ++i) {
    rows[i] = new IntArray(numColumns);
  }
}

IntMatrix::IntMatrix(const IntMatrix & rhs) :
    numRows(rhs.numRows), numColumns(rhs.numColumns) {
  rows = new IntArray *[numRows];

  for (int i = 0; i < numRows; ++i) {
    rows[i] = new IntArray(rhs[i]);
  }
}

IntMatrix::~IntMatrix() {
  for (int i = 0; i < numRows; ++i) {
    delete rows[i];
  }

  delete[] rows;
}

IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    for (int i = 0; i < numRows; ++i) {
      delete rows[i];
    }
    delete[] rows;

    numRows = rhs.numRows;
    numColumns = rhs.numColumns;

    rows = new IntArray *[numRows];
    for (int i = 0; i < numRows; ++i) {
      rows[i] = new IntArray(rhs[i]);
    }
  }
  return *this;
}

int IntMatrix::getRows() const {
  return numRows;
}

int IntMatrix::getColumns() const {
  return numColumns;
}

IntArray & IntMatrix::operator[](int index) {
  assert(index >= 0 && index < numRows);
  return *rows[index];
}

const IntArray & IntMatrix::operator[](int index) const {
  assert(index >= 0 && index < numRows);
  return *rows[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (numRows != rhs.numRows || numColumns != rhs.numColumns) {
    return false;
  }
  for (int i = 0; i < numRows; ++i) {
    if (*rows[i] != rhs[i]) {
      return false;
    }
  }
  return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
  IntMatrix result(numRows, numColumns);
  for (int i = 0; i < numRows; ++i) {
    *result.rows[i] = *rows[i] + rhs[i];
  }
  return result;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); ++i) {
    s << rhs[i];
    if (i < rhs.getRows() - 1) {
      s << ",\n";
    }
  }
  s << " ]";
  return s;
}
