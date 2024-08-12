#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>

#include "../Controller/controller.h"
#include "graphwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {
class View : public QMainWindow {
  Q_OBJECT

 public:
  View(QWidget *parent = nullptr);
  ~View();

 private:
  Ui::View *ui;
  s21::Controller c;
  s21::Graphwindow *g;

 private slots:
  void symbols();
  void operations();
  void functions();
  void result();
  void clearRes();
  void del();
  void makeGraph();
};
}  // namespace s21

#endif  // VIEW_H
