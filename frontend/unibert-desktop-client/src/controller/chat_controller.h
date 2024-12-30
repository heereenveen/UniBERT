#ifndef CHAT_CONTROLLER_H
#define CHAT_CONTROLLER_H

#include <QObject>

class AnswersProvider_I;
class HttpClient_I;
class ChatWindow;

class ChatController : public QObject {
  Q_OBJECT
 public:
  ChatController() = default;
  ~ChatController() = default;

 public:
  void SetUI(ChatWindow* chat_window);
  void SetAnswersProvider(
      const std::shared_ptr<AnswersProvider_I>& http_client);

 public slots:
  void onUiSendQuestion(const QString& str);

 signals:
  void setUiQuestion(const QString& str);
  void addUiAnswer(const QString& str);
  void addUiQuestion(const QString& str);

 protected:
  void connectUiToController();

 protected:
  ChatWindow* chat_window_ = nullptr;
  std::shared_ptr<AnswersProvider_I> answers_provider_ = nullptr;
};

#endif  //CHAT_CONTROLLER_H
