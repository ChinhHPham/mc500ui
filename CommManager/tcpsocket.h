#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QString>

#define TCP_SOCKET TCPSocket::instance();

class Q_DECL_IMPORT TCPSocket : public QObject
{
    Q_OBJECT
public:
    static TCPSocket *instance();
    void doConnect(QString hostName, int port);

signals:
    void dataReceived(const QByteArray &data);

private slots:
    void connected();
    void disconnected();
    void bytesWritten(quint64 bytes);
    void readyRead();

private:
    explicit TCPSocket(QObject *parent = nullptr);
    static TCPSocket *m_instance;
    QTcpSocket *m_socket;
};

#endif // TCPSOCKET_H
