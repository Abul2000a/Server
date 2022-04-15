#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>

class Server: public QTcpServer
{
    Q_OBJECT

public:
    void incomingConnection(qintptr socketDescriptor) override;

public slots:
    void startServer();
    void sockDisc();

private:
    QTcpSocket* socket;
    QByteArray urlsFromFile;
};

#endif // SERVER_H
