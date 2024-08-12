#include "view.h"

#include "ui_view.h"

s21::View::View(QWidget *parent) : QMainWindow(parent), ui(new Ui::View) {
  ui->setupUi(this);
  connect(ui->b0, SIGNAL(clicked()), this, SLOT(symbols()));
  connect(ui->b1, SIGNAL(clicked()), this, SLOT(symbols()));
  connect(ui->b2, SIGNAL(clicked()), this, SLOT(symbols()));
  connect(ui->b3, SIGNAL(clicked()), this, SLOT(symbols()));
  connect(ui->b4, SIGNAL(clicked()), this, SLOT(symbols()));
  connect(ui->b5, SIGNAL(clicked()), this, SLOT(symbols()));
  connect(ui->b6, SIGNAL(clicked()), this, SLOT(symbols()));
  connect(ui->b7, SIGNAL(clicked()), this, SLOT(symbols()));
  connect(ui->b8, SIGNAL(clicked()), this, SLOT(symbols()));
  connect(ui->b9, SIGNAL(clicked()), this, SLOT(symbols()));
  connect(ui->bdot, SIGNAL(clicked()), this, SLOT(symbols()));
  connect(ui->bopen, SIGNAL(clicked()), this, SLOT(symbols()));
  connect(ui->bclose, SIGNAL(clicked()), this, SLOT(symbols()));
  connect(ui->bx, SIGNAL(clicked()), this, SLOT(symbols()));
  connect(ui->be, SIGNAL(clicked()), this, SLOT(symbols()));
  //
  connect(ui->bplus, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->bminus, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->bdiv, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->bmul, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->bpow, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->bmod, SIGNAL(clicked()), this, SLOT(operations()));
  //
  connect(ui->bcos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->bsin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->btan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->bacos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->basin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->batan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->bln, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->blog, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->bsqrt, SIGNAL(clicked()), this, SLOT(functions()));
  //
  connect(ui->beq, SIGNAL(clicked()), this, SLOT(result()));
  //
  connect(ui->bcel, SIGNAL(clicked()), this, SLOT(clearRes()));
  connect(ui->bdel, SIGNAL(clicked()), this, SLOT(del()));
  //
  connect(ui->bgraph, SIGNAL(clicked()), this, SLOT(makeGraph()));
};

s21::View::~View() { delete ui; };

void s21::View::symbols() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label = ui->bresult->text() + button->text();
  ui->bresult->setText(new_label);
};

void s21::View::operations() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label = nullptr;
  if (ui->bresult->text().endsWith('(') || ui->bresult->text().endsWith('e')) {
    new_label = ui->bresult->text() + button->text();
  } else {
    new_label = ui->bresult->text() + ' ' + button->text() + ' ';
  }
  ui->bresult->setText(new_label);
}

void s21::View::functions() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label = ui->bresult->text() + button->text() + '(';
  ui->bresult->setText(new_label);
};

void s21::View::result() {
  QString new_label = ui->bresult->text();
  if (ui->bresult->text().contains("x")) {
    if (ui->bxinput->text().toDouble()) {
      double x = ui->bxinput->text().toDouble();
      c.input_(new_label.toStdString(), x);
      std::pair<double, int> result = c.get_result();
      if (result.second == err_) {
        ui->bresult->setText("Invalid input");
      } else {
        ui->bresult->setText(QString::number(result.first, 'g', 15));
      }
    } else {
      ui->bresult->setText("Invalid input");
    }
  } else {
    c.input_(new_label.toStdString());
    std::pair<double, int> result = c.get_result();
    if (result.second == err_) {
      ui->bresult->setText("Invalid input");
    } else {
      ui->bresult->setText(QString::number(result.first, 'g', 15));
    }
  }
};

void s21::View::clearRes() {
  ui->bresult->setText("");
  ui->bxinput->setText("");
}

void s21::View::del() {
  QString new_label = ui->bresult->text();
  if (ui->bresult->text().endsWith(" "))
    new_label.resize(new_label.size() - 2);
  else
    new_label.resize(new_label.size() - 1);
  ui->bresult->setText(new_label);
};

void s21::View::makeGraph() {
  g = new Graphwindow(this);
  g->show();
};
