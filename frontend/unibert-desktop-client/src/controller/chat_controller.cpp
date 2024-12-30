#include "chat_controller.h"
#include <QtConcurrent/QtConcurrent>
#include "../model/data_provider/answers_provider_i.h"
#include "chatwindow.h"

void ChatController::SetUI(ChatWindow* chat_window) {
  if (chat_window_)
    throw std::invalid_argument("chat window is already set");

  chat_window_ = chat_window;
  connectUiToController();
}

void ChatController::SetAnswersProvider(
    const std::shared_ptr<AnswersProvider_I>& answers_provider) {

  this->answers_provider_ = answers_provider;
}

void ChatController::onUiSendQuestion(const QString& str) {
  emit setUiQuestion("");
  emit addUiQuestion(str);

  auto future = QtConcurrent::run([this, question = str.toStdString()]() {
    return answers_provider_->GetAnswer(question);
  });

  auto watcher = new QFutureWatcher<std::string>(this);

  connect(watcher, &QFutureWatcher<std::string>::finished, this,
          [this, watcher] {
            std::string answer = watcher->result();

            emit addUiAnswer(QString::fromStdString(answer));

            watcher->deleteLater();
          });

  watcher->setFuture(future);
}

void ChatController::connectUiToController() {
  connect(chat_window_, &ChatWindow::sendQuestion, this,
          &ChatController::onUiSendQuestion);
  connect(this, &ChatController::setUiQuestion, chat_window_,
          &ChatWindow::onSetQuestion);
  connect(this, &ChatController::addUiAnswer, chat_window_,
          &ChatWindow::onAddAnswerToChat);
  connect(this, &ChatController::addUiQuestion, chat_window_,
          &ChatWindow::onAddQuestionToChat);
}
