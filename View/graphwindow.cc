#include "graphwindow.h"

#include "../qcustomplot.h"
#include "ui_graphwindow.h"

s21::Graphwindow::Graphwindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Graphwindow) {
  ui->setupUi(this);
  setWindowTitle("Graphic");
  connect(ui->benter, SIGNAL(clicked()), this, SLOT(graph()));
  connect(ui->bclear, SIGNAL(clicked()), this, SLOT(clear()));
};

s21::Graphwindow::~Graphwindow() { delete ui; };

void s21::Graphwindow::graph() {
  forGraph data;
  data.str = ui->fun->text().toStdString();
  if (ui->xMin->text().toDouble()) {
    data.xMin = ui->xMin->text().toDouble();
  } else {
    QMessageBox::warning(this, "Ошибка!", "Ошибка ввода -> xMin");
  }
  if (ui->xMax->text().toDouble()) {
    data.xMax = ui->xMax->text().toDouble();
  } else {
    QMessageBox::warning(this, "Ошибка!", "Ошибка ввода -> xMax");
  }
  if (ui->step->text().toDouble()) data.h = ui->step->text().toDouble();
  if (ui->yMin->text().toDouble()) data.yMin = ui->yMin->text().toDouble();
  if (ui->yMax->text().toDouble()) data.yMax = ui->yMax->text().toDouble();
  if (c.input_forGraph(&data)) {
    ui->widget->xAxis->setRange(data.xMin, data.xMax);
    ui->widget->yAxis->setRange(data.yMin, data.yMax);
    QVector<double> x = QVector<double>(data.x.begin(), data.x.end());
    QVector<double> y = QVector<double>(data.y.begin(), data.y.end());
    ui->widget->addGraph();
    ui->widget->graph(0)->data()->clear();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->setInteraction(QCP::iRangeZoom, true);
    ui->widget->setInteraction(QCP::iRangeDrag, true);
    ui->widget->replot();
    x.clear();
    y.clear();
  } else {
    QMessageBox::warning(this, "Error!", "Invalid input");
  }
};

void s21::Graphwindow::clear() {
  ui->widget->clearGraphs();
  ui->xMin->setText("");
  ui->xMax->setText("");
  ui->yMin->setText("");
  ui->yMax->setText("");
  ui->step->setText("");
  ui->fun->setText("");
}
