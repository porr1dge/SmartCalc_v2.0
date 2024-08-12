#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>
#include <vector>

enum operation {
  number_ = 0,
  minus_ = 1,
  plus_ = 2,
  div_ = 3,
  mul_ = 4,
  mod_ = 5,
  cos_ = 6,
  sin_ = 7,
  tan_ = 8,
  acos_ = 9,
  asin_ = 10,
  atan_ = 11,
  sqrt_ = 12,
  ln_ = 13,
  log_ = 14,
  open_ = 15,
  close_ = 16,
  pow_ = 19,
  err_ = 20
};

struct forGraph {
  double xMin, xMax;
  double yMin, yMax;
  std::vector<double> x, y;
  std::string str;
  double h = 0.1;
};

#endif  // HELPER_H
