/* write your class interface in this file
   write function definitions only if they are very short
 */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cmath>
#include <cstdio>

class Vector2D {
 private:
  double x;
  double y;

 public:
  void initVector(double init_x, double init_y);

  double getMagnitude() const;

  Vector2D operator+(const Vector2D & rhs) const;

  Vector2D & operator+=(const Vector2D & rhs);

  double dot(const Vector2D & rhs) const;

  void print() const;
};

#endif
