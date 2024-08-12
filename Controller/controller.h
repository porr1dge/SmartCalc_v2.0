#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "../Model/model.h"

namespace s21 {
class Controller {
 public:
  Controller(){};
  ~Controller(){};

  void input_(std::string str, double x = 0.0);
  std::pair<double, int> get_result();

  bool input_forGraph(forGraph *data);

 private:
  s21::Model result;
};
}  // namespace s21

#endif  // CONTROLLER_H_