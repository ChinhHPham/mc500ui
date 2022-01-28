#include "tcpsocket.h"

TCPSocket *TCPSocket::m_instance = nullptr;

TCPSocket::TCPSocket(QObject *parent) : QObject(parent)
{

}

TCPSocket *TCPSocket::instance()
{
    if (!m_instance) {
        m_instance = new TCPSocket();
    }
    return m_instance;
}

void TCPSocket::doConnect(QString hostName, int port)
{
    m_socket = new QTcpSocket(this);
    connect(m_socket, &QTcpSocket::connected, this, &TCPSocket::connected);
    connect(m_socket, &QTcpSocket::disconnected, this, &TCPSocket::disconnected);
    connect(m_socket, &QTcpSocket::bytesWritten, this, &TCPSocket::bytesWritten);
    connect(m_socket, &QTcpSocket::readyRead, this, &TCPSocket::readyRead);

    qDebug() << "Connecting to " << hostName << " at port " << port;
    m_socket->connectToHost(hostName, port);
    if(!m_socket->waitForConnected(5000)) {
        qDebug() << "Error: " << m_socket->errorString();
    }
}

void TCPSocket::connected()
{
    qDebug() << "Connection established";
    m_socket->write("");
}

void TCPSocket::disconnected()
{
    qDebug() << "Disconnected to host";
}

void TCPSocket::bytesWritten(quint64 bytes)
{

}

void TCPSocket::readyRead()
{
    const QByteArray data =  m_socket->readAll();
    if (!data.isEmpty()) {
        emit dataReceived(data);
    }
}
