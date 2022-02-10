#include "tcpsocket.h"
#include "commmanager.h"

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
    connect(m_socket, &QTcpSocket::connected, this, [](){qDebug() << QStringLiteral("Connected to host");});
    connect(m_socket, &QTcpSocket::connected, COMM_MANAGER, &CommManager::connectedToHost);
    connect(m_socket, &QTcpSocket::disconnected, this, [](){qDebug() << QStringLiteral("Disconnected to host");});
    connect(m_socket, &QTcpSocket::disconnected, COMM_MANAGER, &CommManager::disconnectedToHost);

    connect(m_socket, &QTcpSocket::readyRead, this, &TCPSocket::readData);
    connect(m_socket, &QAbstractSocket::errorOccurred, this, &TCPSocket::displayError);

    if (hostName.isEmpty()) {
        hostName = QStringLiteral("127.0.0.1");
    }
    if (!port) {
        port = 2535;
    }
    qDebug() << "Connecting to " << hostName << " at port " << port;
    m_socket->connectToHost(hostName, port);
}

void TCPSocket::readData()
{
    const QByteArray data =  m_socket->readAll();
    if (!data.isEmpty()) {
        emit dataReceived(data);
    }
}

void TCPSocket::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::HostNotFoundError:
        qDebug() << "Host not found. Please check the host name and port settings.";
        emit COMM_MANAGER->cannotEstablishConnection();
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() << "Connection is refused. Make sure that server is running and host name and "
                    "port settings are correct.";
        emit COMM_MANAGER->cannotEstablishConnection();
        break;
    default:
        qDebug() << "Error: " << m_socket->errorString();
    }
}

bool TCPSocket::sendData(QByteArray &data)
{
    if (m_socket->isOpen() && m_socket->state() == QAbstractSocket::ConnectedState) {
        m_socket->write(data);
        qDebug() << "Sent data: " << data;
        return true;
    } else {
        qDebug() << "Application is not being connected to any host";
        return false;
    }
}
