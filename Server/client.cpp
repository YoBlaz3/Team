#include "client.h"

Client::Client(QTcpSocket *socket)
{
    this->socket = socket;
    isAuth = false;
}

void Client::sendMessage(QString msg)
{
    QByteArray array = msg.toLocal8Bit();
    char* buffer = array.data();

    socket->write(buffer);
}

bool Client::checkAuth()
{
    return isAuth;
}

QTcpSocket* Client::getSocket()
{
    return this->socket;
}

void Client::setAuth()
{
    this->isAuth = true;
}
