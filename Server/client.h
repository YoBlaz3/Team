#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>



class Client
{
public:
    Client(QTcpSocket *socket);
    void sendMessage(QString msg);
    bool checkAuth();
    void setAuth();
    QTcpSocket* getSocket();
private:
    QTcpSocket* socket;
    bool isAuth;

};

#endif // CLIENT_H
