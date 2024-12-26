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
#include <QTimer>

#include "chatwidget.h"

#include "chatmessage.h"
// #include "ui_ChatWidget.h"


// ChatWidget::ChatWidget(QWidget *parent) :
//     QWidget(parent), ui(new Ui::ChatWidget) {
//     ui->setupUi(this);
// }
//
// ChatWidget::~ChatWidget() {
//     delete ui;
// }
ChatWidget::ChatWidget(QWidget *parent) {
    auto layout = new QVBoxLayout(this);

    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QWidget* messageContainer = new QWidget();
    message_layout_ = new QVBoxLayout(messageContainer);
    message_layout_->setAlignment(Qt::AlignTop);
    scrollArea->setWidget(messageContainer);

    // Input area
    QTextEdit* inputField = new QTextEdit(this);
    inputField->setPlaceholderText("Type a message...");
    QPushButton* sendButton = new QPushButton("Send", this);

    auto inputLayout = new QHBoxLayout();
    inputLayout->addWidget(inputField);
    inputLayout->addWidget(sendButton);

    // Add to the main layout
    layout->addWidget(scrollArea);
    layout->addLayout(inputLayout);

    connect(sendButton, &QPushButton::clicked, this, [=]() {
        QString message = inputField->toPlainText();
        if (!message.isEmpty()) {
            addMessage(message, true); // Add your message
            inputField->clear();

            // Simulate a reply
            QTimer::singleShot(1000, this, [=]() {
                addMessage("This is a reply to: " + message, false);
            });
        }
    });
}

ChatWidget::~ChatWidget() {

}

void ChatWidget::addMessage(const QString &text, bool isSender) {
    ChatMessage* message = new ChatMessage(text, isSender, this);
    message_layout_->addWidget(message);
    adjustSize();
}
