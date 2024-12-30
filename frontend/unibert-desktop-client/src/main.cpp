#include <view/ui_mainwindow.h>

#include <iostream>
#include <ostream>

#include "view/mainwindow.h"

#include <QApplication>
#include <sstream>

#include "controller/chat_controller.h"
#include "model/data_provider/answers_provider_i.h"
#include "model/data_provider/local_answer_provider.h"
#include "model/data_provider/server_answer_provider.h"
#include "model/network/basic_http_client.h"
#include "model/network/http_client_i.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  MainWindow w;

  auto chatWidget = w.UI()->widget;

  auto httpClient = std::make_shared<BasicHttpClient>();
  httpClient->SetInitData({"0.0.0.0", 5000});

  auto dataProvider = std::make_shared<ServerAnswerSupplier>(httpClient);

  auto controller = std::make_shared<ChatController>();
  controller->SetUI(chatWidget);
  controller->SetAnswersProvider(dataProvider);

  w.show();
  return a.exec();
}
