#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>

MyTcpServer::~MyTcpServer()
{
    mTcpServer->close();
    //server_status=0;
}
MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent){
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::Any, 33333)){
        qDebug() << "server is not started";
    } else {
        //server_status=1;
        qDebug() << "server is started";
    }
}

void MyTcpServer::slotNewConnection(){
 //   if(server_status==1){
    auto client = mTcpServer->nextPendingConnection();
    qDebug() << "Client connected";
    clients.push_back(client); //добавляем клиента в конец вектора
    client->write("Hello, World!!! I am echo server!\r\n");
    connect(client, &QTcpSocket::readyRead,this,&MyTcpServer::slotServerRead);
    connect(client,&QTcpSocket::disconnected,this,&MyTcpServer::slotClientDisconnected);
   // }
}

void MyTcpServer::slotServerRead(){ //если один клиент отправил сообщение, то отправляем его всем клиентам, которые подключены
    for (int k = 0; k < clients.size(); k++){
        auto client = clients[k];
        while(client->bytesAvailable()>0)
        {
            QByteArray array =client->readAll();
            for (int e = 0; clients.size(); e++){
                auto sendmessage = clients [e];
                sendmessage->write(array);
            }
        }
     }
}

void MyTcpServer::slotClientDisconnected(){
    int idx = -1;
    for (int k = 0; k < clients.size(); k++){
        auto client = clients[k];
        if (client->state() == QAbstractSocket::UnconnectedState){ //если сокет не соединен, отключаем клиента
            client->disconnect();
            idx = k;
            break;
        }
    }
    //убираем клиента из вектора
    clients.removeAt(idx);
    qDebug() << "Client was disconnected";
}
