#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

class ChatWidget : public QWidget {
  Q_OBJECT

 public:
  explicit ChatWidget(QWidget* parent = nullptr);
  ~ChatWidget() override;

 public:
  void addMessage(const QString& text, bool isSender);

 public slots:
  void resizeEvent(QResizeEvent* event) override;

 private:
  QScrollArea* scrollArea;
  QWidget* containerWidget;
  QVBoxLayout* containerLayout;
};

#endif  //CHATWIDGET_H
