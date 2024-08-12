#include "model.h"

void s21::Model::input_(std::string str, double x) {
  expr = str;
  this->x = x;
  stack_.clear();
  output_.clear();
};

std::pair<double, int> s21::Model::pursing_expr() {
  std::pair<double, int> l = {0.0, 0};
  if (check_brackets()) {
    if (pars()) {
      if (calculate()) {
      } else {
        stack_.clear();
        output_.clear();
        l.second = err_;
        output_.push_front(l);
      }
    } else {
      stack_.clear();
      output_.clear();
      l.second = err_;
      output_.push_front(l);
    }
  } else {
    stack_.clear();
    output_.clear();
    l.second = err_;
    output_.push_front(l);
  }
  return output_.front();
};

bool s21::Model::calculate() {
  bool result = true;
  double num = 0.0;
  double num1 = 0.0;
  int oper = 0;
  while (!stack_.empty() || output_.size() > 1) {
    if (output_.front().second == number_) {
      stack_.push_front(output_.front());
      output_.pop_front();
    } else {
      if (output_.front().second >= cos_ && output_.front().second <= log_) {
        if (stack_.size() > 0 && output_.size() > 0) {
          num = stack_.front().first;
          oper = output_.front().second;
          stack_.pop_front();
          output_.pop_front();
          if (!calc_fun(&num, oper))
            return false;
          else {
            std::pair<double, int> l = {num, number_};
            output_.push_front(l);
          }
        }
      } else {
        if (stack_.size() > 1 && output_.size() > 0) {
          oper = output_.front().second;
          num = stack_.front().first;
          stack_.pop_front();
          num1 = stack_.front().first;
          stack_.pop_front();
          output_.pop_front();
          if (!calc_oper(&num, &num1, oper))
            return false;
          else {
            std::pair<double, int> l = {num, number_};
            output_.push_front(l);
          }
        } else {
          return false;
        }
      }
    }
  }
  return result;
}

bool s21::Model::calc_fun(double *num, int oper) {
  bool res = false;
  if (oper == cos_) {
    *num = cos(*num);
    res = true;
  } else if (oper == sin_) {
    *num = sin(*num);
    res = true;
  } else if (oper == tan_) {
    *num = tan(*num);
    res = true;
  } else if (oper == acos_) {
    *num = acos(*num);
    res = true;
  } else if (oper == asin_) {
    *num = asin(*num);
    res = true;
  } else if (oper == atan_) {
    *num = atan(*num);
    res = true;
  } else if (oper == sqrt_) {
    *num = sqrt(*num);
    res = true;
  } else if (oper == ln_) {
    *num = log(*num);
    res = true;
  } else if (oper == log_) {
    *num = log10(*num);
    res = true;
  }
  return res;
}

bool s21::Model::calc_oper(double *num, double *num1, int oper) {
  bool res = false;
  if (oper == minus_) {
    *num = *num1 - *num;
    res = true;
  } else if (oper == plus_) {
    *num = *num1 + *num;
    res = true;
  } else if (oper == div_) {
    *num = *num1 / *num;
    res = true;
  } else if (oper == mul_) {
    *num = *num1 * *num;
    res = true;
  } else if (oper == mod_) {
    *num = fmod(*num1, *num);
    res = true;
  } else if (oper == pow_) {
    *num = pow(*num1, *num);
    res = true;
  }
  return res;
}

bool s21::Model::check_brackets() {
  int o_b = 0;
  int c_b = 0;
  if (!expr.empty()) {
    for (auto i = expr.begin(); i != expr.end(); ++i) {
      if (*i == '(')
        ++o_b;
      else if (*i == ')')
        ++c_b;
    }
    if (o_b != c_b) return false;
  } else
    return false;
  return true;
};

bool s21::Model::pars() {
  std::pair<double, int> l = {0.0, 0};
  for (auto i = expr.begin(); i != expr.end(); ++i) {
    if (mb_num(*i)) {
      l = numbers(i);
    } else if (*i == 'x') {
      if (*(i - 1) == '-') {
        l.first = this->x * -1;
        l.second = number_;
      } else {
        l.first = this->x;
        l.second = number_;
      }
    } else if (mb_fun(*i)) {
      l = functions(i);
    } else if (*i == ' ') {
      continue;
    } else {
      l = operations(i);
    }
    if (l.second != err_) {
      if (l.second == number_) {
        output_.push_back(l);
      } else if (l.second == open_) {
        stack_.push_front(l);
      } else if (l.second == close_) {
        while (!stack_.empty() && stack_.front().second != open_) {
          output_.push_back(stack_.front());
          stack_.pop_front();
        }
        stack_.pop_front();
      } else {
        if (l.second == minus_ && (*(i + 1) == 'x' || mb_num(*(i + 1))))
          continue;
        if (l.second == plus_ && (*(i + 1) == 'x' || mb_num(*(i + 1))))
          continue;
        if (check_prior(l) > check_prior(stack_.front()))
          stack_.push_front(l);
        else if (check_prior(l) <= check_prior(stack_.front())) {
          if (l.second == pow_) {
            while (!stack_.empty() &&
                   (check_prior(l) < check_prior(stack_.front()))) {
              output_.push_back(stack_.front());
              stack_.pop_front();
            }
          } else {
            while (!stack_.empty() &&
                   (check_prior(l) <= check_prior(stack_.front()))) {
              output_.push_back(stack_.front());
              stack_.pop_front();
            }
          }
          stack_.push_front(l);
        }
      }
    } else {
      stack_.clear();
      output_.clear();
      return false;
    }
  }
  while (!stack_.empty()) {
    output_.push_back(stack_.front());
    stack_.pop_front();
  }
  return true;
}

int s21::Model::check_prior(std::pair<double, int> l) {
  int res = 0;
  if (l.second >= minus_ && l.second <= plus_)
    res = 1;
  else if (l.second >= div_ && l.second <= mod_)
    res = 2;
  else if (l.second == pow_)
    res = 3;
  else if (l.second >= cos_ && l.second <= log_)
    res = 4;
  return res;
};

std::pair<double, int> s21::Model::numbers(std::string::iterator &n) {
  std::pair<double, int> l = {0.0, 0};
  size_t s = n - expr.begin();
  size_t pos = s;
  int dots = 0;
  int e = 0;
  for (; pos < expr.size() && mb_num(expr.at(pos)); ++pos) {
    if (expr.at(pos) == '.') ++dots;
    if (expr.at(pos) == 'e') {
      ++e;
      if (expr.at(pos + 1) == '-' || expr.at(pos + 1) == '+') pos += 2;
    }
  }
  if (dots > 1) l.second = err_;
  if (e > 1) l.second = err_;
  std::string sep = expr.substr(s, pos - s);
  l.first = atof(sep.c_str());
  if (*(n - 1) == '-') {
    l.first *= -1;
  } else if (*(n - 1) == '+') {
    l.first *= 1;
  }
  n += (sep.size() - 1);
  return l;
};

std::pair<double, int> s21::Model::functions(std::string::iterator &n) {
  std::pair<double, int> l = {0.0, 0};
  size_t s = n - expr.begin();
  size_t pos = s;
  for (; pos < expr.size() && mb_fun(expr.at(pos)); ++pos) {
    ;
  }
  std::string sep = expr.substr(s, pos - s);
  int res = check_fun(sep);
  l.second = res;
  n += (sep.size() - 1);
  return l;
};

std::pair<double, int> s21::Model::operations(std::string::iterator &n) {
  std::pair<double, int> l = {0.0, err_};
  size_t i = 0;
  int check = 0;
  for (; i < 7; ++i) {
    if (*n == operation_[i].first) {
      check = 1;
      break;
    }
  }
  if (check) l.second = operation_[i].second;
  return l;
};

bool s21::Model::mb_num(char ch) {
  if ((ch >= '0' && ch <= '9') || (ch == '.' || ch == 'e')) return true;
  return false;
};

bool s21::Model::mb_fun(char ch) {
  if (ch >= 'a' && ch <= 'z' && (ch != 'e')) return true;
  return false;
};

int s21::Model::check_fun(std::string str) {
  if (str == function_[0])
    return mod_;
  else if (str == function_[1])
    return cos_;
  else if (str == function_[2])
    return sin_;
  else if (str == function_[3])
    return tan_;
  else if (str == function_[4])
    return acos_;
  else if (str == function_[5])
    return asin_;
  else if (str == function_[6])
    return atan_;
  else if (str == function_[7])
    return sqrt_;
  else if (str == function_[8])
    return ln_;
  else if (str == function_[9])
    return log_;
  return err_;
};

bool s21::Model::points(forGraph *data) {
  bool result = true;
  if (data->str.find('x') || data->str[0] == 'x') {
    for (double X = data->xMin; X < data->xMax; X += data->h) {
      data->x.push_back(X);
      input_(data->str, X);
      std::pair<double, int> l = pursing_expr();
      data->y.push_back(l.first);
    }
  } else
    result = false;

  return result;
};

void s21::Model::print() {
  std::cout.precision(15);
  if (output_.front().second != err_)
    std::cout << output_.front().first;
  else
    std::cout << "Invalid input!!!";
};
