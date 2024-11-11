#ifndef POLY_HPP
#define POLY_HPP

#include <algorithm>
#include <iostream>
#include <vector>

template<typename NumT>
class Polynomial {
 private:
  std::vector<NumT> coefficients;
  friend class Polynomial;

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
    for (size_t i = 0; i < result.coefficients.size(); i++) {
      result.coefficients[i] = -result.coefficients[i];
    }
    return result;
  }

  Polynomial operator*(const NumT & scalar) const {
    Polynomial result = *this;
    for (size_t i = 0; i < result.coefficients.size(); i++) {
      result.coefficients[i] *= scalar;
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

  NumT eval(const NumT & x) const {
    NumT result = 0;
    NumT power_of_x = 1;
    for (size_t i = 0; i < coefficients.size(); i++) {
      result += coefficients[i] * power_of_x;
      power_of_x *= x;
    }
    return result;
  }

  Polynomial derivative() const {
    Polynomial result;
    if (coefficients.size() <= 1) {
      return result;
    }
    result.coefficients.resize(coefficients.size() - 1, NumT(0));
    for (size_t i = 1; i < coefficients.size(); i++) {
      result.coefficients[i - 1] = NumT(i) * coefficients[i];
    }
    result.trim();
    return result;
  }

  template<typename OtherNumT>
  Polynomial<OtherNumT> convert() const {
    Polynomial<OtherNumT> result;
    result.coefficients.resize(coefficients.size());
    for (size_t i = 0; i < coefficients.size(); i++) {
      result.coefficients[i] = OtherNumT(coefficients[i]);
    }
    return result;
  }

  // The findZero function within the Polynomial class
  template<typename ToleranceType>
  NumT findZero(NumT initial_guess,
                unsigned max_steps,
                const ToleranceType & tolerance,
                const ToleranceType & deriv_tolerance) {
    Polynomial<NumT> deriv = derivative();
    NumT current_x = initial_guess;

    for (unsigned steps_remaining = max_steps; steps_remaining > 0; --steps_remaining) {
      NumT y = eval(current_x);

      // Check if we are close enough to zero
      if (std::abs(y) <= tolerance) {
        return current_x;
      }

      NumT dy = deriv.eval(current_x);

      // Check if the derivative is too close to zero
      if (std::abs(dy) < deriv_tolerance) {
        throw convergence_failure<NumT>(current_x);
      }

      // Update x based on the Newton-Raphson method
      current_x = current_x - y / dy;
    }
    throw convergence_failure<NumT>(current_x);
  }

  // The convergence_failure exception class
  template<typename ValueType>
  class convergence_failure : public std::exception {
   public:
    const ValueType value;

    explicit convergence_failure(const ValueType & x) : value(x) {}

    virtual const char * what() const throw() { return "Convergence failure"; }
  };

  NumT operator()(const NumT & x) const { return eval(x); }
};

#endif  // POLY_HPP
