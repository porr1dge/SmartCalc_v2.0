#include <QApplication>

#include "View/view.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::View w;
  w.setWindowTitle("SmartCalc_v2");
  w.show();
  return a.exec();
}
