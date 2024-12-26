#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "chatwindow.h"


#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_chatOpen_clicked() {
    auto* chat = new ChatWindow(nullptr);
    chat->setAttribute(Qt::WA_DeleteOnClose);
    chat->show();

}