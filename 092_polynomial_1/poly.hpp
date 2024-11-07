#ifndef POLY_HPP
#define POLY_HPP

#include <algorithm>
#include <iostream>
#include <vector>

template<typename NumT>
class Polynomial {
 private:
  std::vector<NumT> coefficients;

  void trim() {
    while (!coefficients.empty() && coefficients.back() == NumT(0)) {
      coefficients.pop_back();
    }
    if (coefficients.empty()) {
      coefficients.push_back(NumT(0));
    }
  }

 public:
  Polynomial() : coefficients(1, NumT(0)) {}

  void addTerm(const NumT & c, unsigned p) {
    if (p >= coefficients.size()) {
      coefficients.resize(p + 1, NumT(0));
    }
    coefficients[p] += c;
    trim();
  }

  Polynomial operator+(const Polynomial & rhs) const {
    Polynomial result = *this;
    if (rhs.coefficients.size() > result.coefficients.size()) {
      result.coefficients.resize(rhs.coefficients.size(), NumT(0));
    }
    for (size_t i = 0; i < rhs.coefficients.size(); i++) {
      result.coefficients[i] += rhs.coefficients[i];
    }
    result.trim();
    return result;
  }

  Polynomial operator-(const Polynomial & rhs) const {
    Polynomial result = *this;
    if (rhs.coefficients.size() > result.coefficients.size()) {
      result.coefficients.resize(rhs.coefficients.size(), NumT(0));
    }
    for (size_t i = 0; i < rhs.coefficients.size(); i++) {
      result.coefficients[i] -= rhs.coefficients[i];
    }
    result.trim();
    return result;
  }

  Polynomial operator-() const {
    Polynomial result = *this;
    for (auto & coef : result.coefficients) {
      coef = -coef;
    }
    return result;
  }

  Polynomial operator*(const NumT & scalar) const {
    Polynomial result = *this;
    for (auto & coef : result.coefficients) {
      coef *= scalar;
    }
    result.trim();
    return result;
  }

  Polynomial operator*(const Polynomial & rhs) const {
    Polynomial result;
    result.coefficients.resize(coefficients.size() + rhs.coefficients.size() - 1,
                               NumT(0));
    for (size_t i = 0; i < coefficients.size(); i++) {
      for (size_t j = 0; j < rhs.coefficients.size(); j++) {
        result.coefficients[i + j] += coefficients[i] * rhs.coefficients[j];
      }
    }
    result.trim();
    return result;
  }

  bool operator==(const Polynomial & rhs) const {
    return coefficients == rhs.coefficients;
  }

  bool operator!=(const Polynomial & rhs) const { return !(*this == rhs); }

  Polynomial & operator+=(const Polynomial & rhs) {
    *this = *this + rhs;
    return *this;
  }

  Polynomial & operator-=(const Polynomial & rhs) {
    *this = *this - rhs;
    return *this;
  }

  Polynomial & operator*=(const Polynomial & rhs) {
    *this = *this * rhs;
    return *this;
  }

  Polynomial & operator*=(const NumT & scalar) {
    *this = *this * scalar;
    return *this;
  }

  friend std::ostream & operator<<(std::ostream & os, const Polynomial<NumT> & p) {
    bool first = true;
    for (size_t i = p.coefficients.size(); i > 0; i--) {
      NumT coef = p.coefficients[i - 1];
      if (coef != NumT(0)) {
        if (!first) {
          os << " + ";
        }
        os << coef << "*x^" << (i - 1);
        first = false;
      }
    }
    if (first) {
      os << NumT(0);
    }
    return os;
  }
};

#endif  // POLY_HPP
