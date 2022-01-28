#include "commmanager.h"
#include "protoparser.h"
#include "tcpsocket.h"

CommManager *CommManager::m_instance = nullptr;

CommManager *CommManager::instance()
{
    if (!m_instance) {
        m_instance = new CommManager();
    }
    return m_instance;
}

CommManager::CommManager(QObject *parent) : QObject(parent)
{
    m_protoParser = new ProtoParser(this);
    connect(TCPSocket::instance(), &TCPSocket::dataReceived, this, &CommManager::dataReceived);
    connect(m_protoParser, &ProtoParser::positionUpdated, this, &CommManager::positionUpdated);
    connect(m_protoParser, &ProtoParser::feedHoldPressed, this, &CommManager::feedHoldPressed);
    connect(m_protoParser, &ProtoParser::currentStepChanged, this, &CommManager::currentStepChanged);
    connect(m_protoParser, &ProtoParser::cycleStopped, this, &CommManager::cycleStopped);
}

void CommManager::dataReceived(const QByteArray &data)
{
    m_protoParser->parseMessage(data);
}
