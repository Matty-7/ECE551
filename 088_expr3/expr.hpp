#ifndef EXPR_HPP
#define EXPR_HPP

#include <sstream>
#include <stdexcept>
#include <string>

class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual long evaluate() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
 private:
  long value;

 public:
  NumExpression(long val) : value(val) {}
  std::string toString() const {
    std::ostringstream oss;
    oss << value;
    return oss.str();
  }

  long evaluate() const { return value; }
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

  std::string toString() const {
    return "(" + lhs->toString() + "+" + rhs->toString() + ")";
  }

  long evaluate() const { return lhs->evaluate() + rhs->evaluate(); }
};

class MinusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  MinusExpression(Expression * left, Expression * right) : lhs(left), rhs(right) {}
  ~MinusExpression() {
    delete lhs;
    delete rhs;
  }
  std::string toString() const {
    return "(" + lhs->toString() + " - " + rhs->toString() + ")";
  }

  long evaluate() const { return lhs->evaluate() - rhs->evaluate(); };
};

class TimesExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  TimesExpression(Expression * left, Expression * right) : lhs(left), rhs(right) {}
  ~TimesExpression() {
    delete lhs;
    delete rhs;
  }
  std::string toString() const {
    return "(" + lhs->toString() + "*" + rhs->toString() + ")";
  }

  long evaluate() const { return lhs->evaluate() * rhs->evaluate(); }
};

class DivExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  DivExpression(Expression * left, Expression * right) : lhs(left), rhs(right) {}
  ~DivExpression() {
    delete lhs;
    delete rhs;
  }
  std::string toString() const {
    return "(" + lhs->toString() + " / " + rhs->toString() + ")";
  }

  long evaluate() const {
    long rhs_value = rhs->evaluate();
    if (rhs_value == 0) {
      throw std::runtime_error("Division by zero error");
    }
    return lhs->evaluate() / rhs_value;
  }
};

#endif
