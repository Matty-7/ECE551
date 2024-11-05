#ifndef EXPR_HPP
#define EXPR_HPP

#include <sstream>
#include <string>

class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
 private:
  long value;

 public:
  NumExpression(long val) : value(val) {}
  std::string toString() const override {
    std::ostringstream oss;
    oss << value;
    return oss.str();
  }
};

class PlusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * left, Expression * right) : lhs(left), rhs(right) {}
  ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
  std::string toString() const override {
    return "(" + lhs->toString() + " + " + rhs->toString() + ")";
  }
};

#endif
