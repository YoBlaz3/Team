#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QtNetwork>
#include <QByteArray>
#include <QDebug>
#include <QVector>

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
    QTcpServer * mTcpServer;
    QVector <QTcpSocket*> clients;
    //int server_status;
};
#endif // MYTCPSERVER_H







