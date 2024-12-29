#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>

#include "chatwidget.h"
#include "../cmake-build-debug/unibert-desktop-client_autogen/include/ui_chatwindow.h"


class ChatWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();

public slots:
    void on_sendMessage_clicked();
    void on_messageEdit_returnPressed();
    void on_discardMessage_clicked();

protected:
    Ui::ChatWindow *ui;
    ChatWidget *chat_widget;
};

#endif // CHATWINDOW_H
