#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "chatwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui;
}
const Ui::MainWindow* MainWindow::UI() {
  return ui;
}
