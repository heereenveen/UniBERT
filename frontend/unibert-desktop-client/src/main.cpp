#include <view/ui_mainwindow.h>

#include <iostream>
#include <ostream>

#include "view/mainwindow.h"

#include <QApplication>
#include <sstream>

#include "controller/chat_controller.h"
#include "model/data_provider/answers_provider_i.h"
#include "model/data_provider/local_answer_provider.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  MainWindow w;

  auto chatWidget = w.UI()->widget;
  auto dataProvider = std::make_shared<LocalAnswerProvider>();

  auto controller = std::make_shared<ChatController>();
  controller->SetUI(chatWidget);
  controller->SetAnswersProvider(dataProvider);

  w.show();
  return a.exec();
}
