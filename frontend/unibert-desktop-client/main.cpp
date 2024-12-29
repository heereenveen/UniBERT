#include <iostream>
#include <ostream>

#include "view/mainwindow.h"

#include <QApplication>
#include <sstream>

#include "model/basic_http_client.h"

int main(int argc, char *argv[])
{
    BasicHttpClient client( R"(http://example.com/)" );
    auto res = client.SendEmptyGetRequest();
    std::cout << res.get() << std::endl;

    // QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    // return a.exec();
}
