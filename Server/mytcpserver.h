#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H
#include "client.h"

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include <QtNetwork>
#include <QByteArray>
#include <QDebug>
#include <QSqlDatabase>

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);
    ~MyTcpServer();
public slots:
    void slotNewConnection();
    void slotClientDisconnected();
    void slotServerRead();
private:
    QSqlDatabase db;
    QTcpServer *mTcpServer;
    QVector<Client*> clients;

    //int server_status;
};
#endif // MYTCPSERVER_H







