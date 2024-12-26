#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#include <QWidget>

namespace Ui {
class ChatMessage;
}

class ChatMessage : public QWidget
{
    Q_OBJECT

public:
    explicit ChatMessage(const QString& text, bool isSender, QWidget* parent = nullptr);
    ~ChatMessage();

protected:
    void paintEvent(QPaintEvent* event) override;

    QSize sizeHint() const override;


private:
    QString message_text_;
    bool is_sender_;
    // Ui::ChatMessage *ui;
};

#endif // CHATMESSAGE_H
