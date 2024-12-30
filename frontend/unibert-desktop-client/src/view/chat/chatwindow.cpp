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

const Ui::ChatWindow* ChatWindow::UI() const {
  return ui;
}

void ChatWindow::on_sendMessage_clicked() {
  emit sendQuestion(ui->messageEdit->text());
}

void ChatWindow::on_messageEdit_returnPressed() {
  emit sendQuestion(ui->messageEdit->text());
}

void ChatWindow::on_discardMessage_clicked() {
  onSetQuestion("");
}

void ChatWindow::onSetQuestion(const QString& str) {
  ui->messageEdit->setText(str);
}

void ChatWindow::onAddAnswerToChat(const QString& str) {
  ui->chatWidget->addMessage(str, false);
}
void ChatWindow::onAddQuestionToChat(const QString& str) {
  ui->chatWidget->addMessage(str, true);
}
