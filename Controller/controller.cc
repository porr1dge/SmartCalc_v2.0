#include "controller.h"

void s21::Controller::input_(std::string str, double x) {
  result.input_(str, x);
}

std::pair<double, int> s21::Controller::get_result() {
  return result.pursing_expr();
};

bool s21::Controller::input_forGraph(forGraph *data) {
  return result.points(data);
};