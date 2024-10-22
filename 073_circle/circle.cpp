#include "circle.hpp"

#include <algorithm>
#include <cmath>

Circle::Circle(const Point & c, double r) : center(c), radius(r) {
}

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & other) const {
  double d = center.distanceFrom(other.center);
  if (d >= radius + other.radius) {
    return 0.0;
  }
  if (d <= std::abs(radius - other.radius)) {
    double smallerRadius = std::min(radius, other.radius);
    return M_PI * smallerRadius * smallerRadius;
  }

  double r1_sq = radius * radius;
  double r2_sq = other.radius * other.radius;

  double part1 = r1_sq * std::acos((d * d + r1_sq - r2_sq) / (2 * d * radius));
  double part2 = r2_sq * std::acos((d * d + r2_sq - r1_sq) / (2 * d * other.radius));
  double part3 =
      0.5 * std::sqrt((-d + radius + other.radius) * (d + radius - other.radius) *
                      (d - radius + other.radius) * (d + radius + other.radius));

  return part1 + part2 - part3;
}
