#include "chatwindow.h"

#include "chatwidget.h"

ChatWindow::ChatWindow(QWidget* parent)
    : QWidget{parent}, ui(new Ui::ChatWindow) {
  ui->setupUi(this);
  setContentsMargins(0, 0, 0, 0);
}

ChatWindow::~ChatWindow() {
  delete ui;
}

static bool is_sender = false;
void ChatWindow::on_sendMessage_clicked() {
  is_sender = !is_sender;
  auto text = ui->messageEdit->text();
  ui->chatWidget->addMessage(text, is_sender);
}

void ChatWindow::on_messageEdit_returnPressed() {}

void ChatWindow::on_discardMessage_clicked() {}
