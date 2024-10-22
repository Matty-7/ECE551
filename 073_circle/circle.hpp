#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "point.hpp"

class Circle {
 private:
  Point center;
  const double radius;

 public:
  Circle(const Point & c, double r);
  void move(double dx, double dy);
  double intersectionArea(const Circle & other) const;
};

#endif
