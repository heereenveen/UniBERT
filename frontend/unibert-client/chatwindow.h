#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>

class ChatWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ChatWindow(QWidget *parent = nullptr);

signals:
};

#endif // CHATWINDOW_H
