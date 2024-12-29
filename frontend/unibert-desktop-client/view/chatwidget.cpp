#include <QApplication>
#include <QDateTime>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QScrollArea>
#include <QSpacerItem>
#include <QStyleOption>
#include <QTextEdit>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

#include "chatwidget.h"

#include "chatmessage.h"

ChatWidget::ChatWidget(QWidget* parent) : QWidget(parent) {

  // Create a QScrollArea
  scrollArea = new QScrollArea(this);
  scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  scrollArea->setWidgetResizable(true);

  scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  // Create a container widget for the scroll area
  containerWidget = new QWidget();
  containerLayout = new QVBoxLayout(containerWidget);
  containerLayout->setContentsMargins(0, 0, 0, 0);

  containerLayout->setAlignment(Qt::AlignTop);
  // Set layout to containerWidget
  containerWidget->setLayout(containerLayout);
  scrollArea->setWidget(containerWidget);

  // Main layout of the CustomWidget
  auto* mainLayout = new QVBoxLayout(this);
  mainLayout->addWidget(scrollArea);
  setLayout(mainLayout);

  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  // setMinimumSize(300, 400); // Set a minimum size to prevent shrinking too much
}

ChatWidget::~ChatWidget() {}

void ChatWidget::addMessage(const QString& text, bool isSender) {
  auto* message = new ChatMessage(text, isSender, this);
  message->setMaximumWidth(scrollArea->width() * 0.6);

  QHBoxLayout* container = new QHBoxLayout();

  if (isSender) {
    // Add stretch space to the left and the message to the right
    container->addStretch();
    container->addWidget(message);
  } else {
    // Add the message to the left and stretch space to the right
    container->addWidget(message);
    container->addStretch();
  }

  // Add the container layout to the vertical layout
  containerLayout->addLayout(container);

  // containerLayout->addWidget(message);
  // adjustSize();
}

void ChatWidget::resizeEvent(QResizeEvent* event) {
  QWidget::resizeEvent(event);
  for (int i = 0; i < containerLayout->count(); ++i) {
    QWidget* item = containerLayout->itemAt(i)->widget();
    if (item) {
      item->setMaximumWidth(scrollArea->width() * 0.6);
    }
  }
}
