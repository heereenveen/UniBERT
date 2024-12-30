#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>

#include "../cmake-build-debug/unibert-desktop-client_autogen/include/ui_chatwindow.h"
#include "chatwidget.h"

class ChatWindow : public QWidget {
  Q_OBJECT
 public:
  explicit ChatWindow(QWidget* parent = nullptr);
  ~ChatWindow();

 public:
  const Ui::ChatWindow* UI() const;

  // autogen slots
 public slots:
  void on_sendMessage_clicked();
  void on_messageEdit_returnPressed();
  void on_discardMessage_clicked();

  // custom slots, we will use them in controller
 public slots:
  void onSetQuestion(const QString& str);
  void onAddAnswerToChat(const QString& str);
  void onAddQuestionToChat(const QString& str);

  // customSignals
 signals:
  void sendQuestion(const QString& str);

 protected:
  Ui::ChatWindow* ui;
};

#endif  // CHATWINDOW_H
