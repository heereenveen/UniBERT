#include "chatmessage.h"

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QDateTime>
#include <QSpacerItem>
#include <QStyleOption>
#include <QPainter>

ChatMessage::ChatMessage(const QString &text, bool isSender, QWidget *parent)
    : QWidget(parent),
    message_text_(text),
    is_sender_(isSender)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

ChatMessage::~ChatMessage()
{
    // delete ui;
}

void ChatMessage::paintEvent(QPaintEvent *event) {
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    QRect bubbleRect = QRect(10, 10, width() - 20, height() - 20);

    QColor bubbleColor = is_sender_ ? QColor("#D2F8FF") : QColor("#F1F1F1");
    painter.setBrush(bubbleColor);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(bubbleRect, 10, 10);

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 10));
    painter.drawText(bubbleRect.adjusted(10, 10, -10, -10), Qt::TextWordWrap, message_text_);

    QWidget::paintEvent(event);
}

QSize ChatMessage::sizeHint() const  {
    QFontMetrics metrics(font());
    int textWidth = width() - 40;
    QRect textRect = metrics.boundingRect(0, 0, textWidth, 0, Qt::TextWordWrap, message_text_);
    return QSize(width(), textRect.height() + 30);
}