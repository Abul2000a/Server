#include "server.h"
#include <QFile>
#include <QDir>


void Server::startServer()
{
    if (this->listen(QHostAddress::Any,5555))
    {
        qDebug() << "Listening";
        QString path = QDir::currentPath() + "/urls.txt";
        QFile textFile(path);
        if (textFile.open(QIODevice::ReadOnly)){
            while (!textFile.atEnd()){
                urlsFromFile.append(textFile.readLine());
                urlsFromFile.append("...");
            }
        }
    }
    else
    {
        qDebug() << "Not listening";
    }
}


void Server::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, &QTcpSocket::disconnected, this, &Server::sockDisc);

    qDebug() << socketDescriptor << " Client connected";

    qDebug() << "Send client connect status - YES";

    socket->write(urlsFromFile);
}



void Server::sockDisc()
{
    if (dynamic_cast<QTcpSocket*>(sender())){
        sender()->deleteLater();
    }
}
