#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QMainWindow>

#include "../Controller/controller.h"
#include "../Model/helper.h"

namespace Ui {
class Graphwindow;
}

namespace s21 {
class Graphwindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit Graphwindow(QWidget *parent = nullptr);
  ~Graphwindow();

 private:
  Ui::Graphwindow *ui;
  s21::Controller c;

 private slots:
  void graph();
  void clear();
};
}  // namespace s21

#endif  // GRAPHWINDOW_H
