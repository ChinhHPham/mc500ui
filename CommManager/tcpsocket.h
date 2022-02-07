#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QString>

#define TCP_SOCKET TCPSocket::instance()

class TCPSocket : public QObject
{
    Q_OBJECT
public:
    static TCPSocket *instance();
    void doConnect(QString hostName, int port);
    bool sendData(QByteArray &data);

signals:
    void dataReceived(const QByteArray &data);

private slots:
    void readData();
    void displayError(QAbstractSocket::SocketError socketError);

private:
    explicit TCPSocket(QObject *parent = nullptr);
    static TCPSocket *m_instance;
    QTcpSocket *m_socket;
};

#endif // TCPSOCKET_H
