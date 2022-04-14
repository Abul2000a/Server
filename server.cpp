#include "server.h"
#include <QFile>
#include <QDir>



void Server::startServer()
{
    if (this->listen(QHostAddress::Any,5555))
    {

        qDebug() << "Listening";

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

    connect(socket, &QTcpSocket::readyRead, this, &Server::sockReady);
    connect(socket, &QTcpSocket::disconnected, this, &Server::sockDisc);

    qDebug() << socketDescriptor << " Client connected";
    QString path = QDir::currentPath() + "/urls.txt";
    qDebug() << path;
    QFile textFile(path);
        if (textFile.open(QIODevice::ReadOnly)){
            QTextStream textStream(&textFile);
            while (!textStream.atEnd()){
                textStream >> Data;
                socket->write(Data);
            }
        }
    qDebug() << "Send client connect status - YES";
}


void Server::sockReady()
{
    qDebug() << "Ready!";
}


void Server::sockDisc()
{

    if (dynamic_cast<QTcpSocket*>(sender())){

        qDebug() << "Disconnect" ;
        qInfo() << "deleting..." << socket;
        sender()->deleteLater();
    }

}
