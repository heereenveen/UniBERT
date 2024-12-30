#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#include <QFrame>
#include <QWidget>

class QLabel;
namespace Ui {
class ChatMessage;
}

class ChatMessage : public QWidget {
  Q_OBJECT

 public:
  explicit ChatMessage(const QString& text, bool isSender,
                       QWidget* parent = nullptr);
  ~ChatMessage();

 public:
  void paintEvent(QPaintEvent* event);

 protected:
  QSize textSize() const;
  QSize sizeHint() const override;

  int maxWidthForText() const;

 protected:
  QLabel* textLabel;
  QString message_text_;

  int paddingToText;

 protected:
  bool is_sender_;

  // Ui::ChatMessage *ui;
};

#endif  // CHATMESSAGE_H
