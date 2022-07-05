#include "mainwindow.h"

#include <QApplication>
singletonclient * singletonclient::p_instance;
SingletonDestroyer singletonclient::destroyer;
QTcpSocket singletonclient::mTcpSocket;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();
    return a.exec();
}
