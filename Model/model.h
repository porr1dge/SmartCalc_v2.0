#ifndef MODEL_H_
#define MODEL_H_
#include <cmath>
#include <iostream>
#include <list>
#include <string>

#include "helper.h"

namespace s21 {
class Model {
 public:
  Model(){};
  ~Model(){};

  void input_(std::string str, double x = 0);
  std::pair<double, int> pursing_expr();
  bool check_brackets();
  bool pars();
  std::pair<double, int> numbers(std::string::iterator &n);
  std::pair<double, int> functions(std::string::iterator &n);
  std::pair<double, int> operations(std::string::iterator &n);
  bool calculate();
  bool calc_fun(double *num, int oper);
  bool calc_oper(double *num, double *num1, int oper);
  bool mb_num(char ch);
  bool mb_fun(char ch);
  int check_fun(std::string str);
  int check_prior(std::pair<double, int> l);
  bool points(forGraph *data);
  void print();

  std::vector<std::string> function_ = {"mod",  "cos",  "sin",  "tan", "acos",
                                        "asin", "atan", "sqrt", "ln",  "log"};

  std::vector<std::pair<char, int>> operation_ = {
      {'+', plus_}, {'-', minus_}, {'*', mul_},  {'/', div_},
      {'^', pow_},  {'(', open_},  {')', close_}};

 private:
  std::list<std::pair<double, int>> stack_;
  std::list<std::pair<double, int>> output_;
  std::string expr;
  double x;
};
}  // namespace s21

#endif  // MODEL_H_