//
// Created by notnuff on 25.12.24.
//

#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include <QVBoxLayout>


QT_BEGIN_NAMESPACE
namespace Ui { class ChatWidget; }
QT_END_NAMESPACE

class ChatWidget : public QWidget {
Q_OBJECT

public:
    explicit ChatWidget(QWidget *parent = nullptr);
    ~ChatWidget() override;


public:
    void addMessage(const QString& text, bool isSender);

private:
    QVBoxLayout* message_layout_;

    // Ui::ChatWidget *ui;
};


#endif //CHATWIDGET_H
