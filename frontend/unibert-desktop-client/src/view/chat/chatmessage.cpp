#include "chatmessage.h"

#include <QApplication>
#include <QDateTime>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QScrollArea>
#include <QSpacerItem>
#include <QStyleOption>
#include <QTextBrowser>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

ChatMessage::ChatMessage(const QString& text, bool isSender, QWidget* parent)
    : QWidget(parent), message_text_(text), is_sender_(isSender) {
  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

  setFont(QFont("Arial", 20));
  paddingToText = 20;
}

ChatMessage::~ChatMessage() {
  // delete ui;
}
void ChatMessage::paintEvent(QPaintEvent* event) {
  QStyleOption opt;
  opt.initFrom(this);
  QPainter painter(this);

  painter.setRenderHint(QPainter::Antialiasing);

  QColor bubbleColor = is_sender_ ? QColor("#D2F8FF") : QColor("#F1F1F1");
  painter.setBrush(bubbleColor);
  painter.setPen(Qt::NoPen);
  painter.drawRoundedRect(rect(), 10, 10);

  painter.setPen(Qt::black);
  painter.setFont(font());

  QRect messageRect = QRect(paddingToText, paddingToText,
                            width() - paddingToText, height() - paddingToText);

  painter.drawText(messageRect, Qt::TextWordWrap | Qt::TextWrapAnywhere,
                   message_text_);

  QWidget::paintEvent(event);
}

QSize ChatMessage::textSize() const {
  auto max = maxWidthForText();
  QFontMetrics metrics(font());

  QRect textRect =
      metrics.boundingRect(0, 0, max, 0, Qt::TextWrapAnywhere, message_text_);

  return textRect.size();
}

QSize ChatMessage::sizeHint() const {
  auto text_size = textSize();
  return QSize(text_size.width() + paddingToText * 2,
               text_size.height() + paddingToText * 2);
}
int ChatMessage::maxWidthForText() const {
  auto max = maximumWidth();
  return max - paddingToText * 2;
}