#include "commmanager.h"
#include "protoparser.h"
#include "tcpsocket.h"
#include <QtGlobal>

CommManager *CommManager::m_instance = nullptr;

CommManager *CommManager::instance()
{
    if (!m_instance) {
        m_instance = new CommManager();
    }
    return m_instance;
}

void CommManager::initTCPConnection()
{
//Get host name and port from environment variables and establish connection
#ifdef DEBUG_MODE
    //Replace host IP address and port number with actual value
    const QString hostName = QLatin1String("10.0.2.15");
    const int portNum = 41409;
    TCP_SOCKET->doConnect(hostName, portNum);
#else
    TCP_SOCKET->doConnect(qEnvironmentVariable("MC_HOSTNAME"), qEnvironmentVariableIntValue("MC_PORT"));
#endif
}

bool CommManager::updatePosition(const PositionExact &pos)
{
    QByteArray dataMessage = m_protoParser->serializePositionUpdate(pos);
    return TCP_SOCKET->sendData(dataMessage);
}

bool CommManager::updateFeedHoldStatus(bool isPressed)
{
    QByteArray dataMessage = m_protoParser->serializeFeedHoldMessage(isPressed);
    return TCP_SOCKET->sendData(dataMessage);
}

bool CommManager::cycleStart()
{
    QByteArray dataMessage = m_protoParser->serializeCycleStart();
    return TCP_SOCKET->sendData(dataMessage);
}

bool CommManager::clearProgram()
{
    QByteArray dataMessage = m_protoParser->serializeClearProgram();
    return TCP_SOCKET->sendData(dataMessage);
}

bool CommManager::addProgramLine(const ProgramLine &pLine)
{
    QByteArray dataMessage = m_protoParser->serializeAddProgramLine(pLine);
    return TCP_SOCKET->sendData(dataMessage);
}

CommManager::CommManager(QObject *parent) : QObject(parent)
{
    m_protoParser = new ProtoParser(this);
    connect(TCP_SOCKET, &TCPSocket::dataReceived, this, &CommManager::dataReceived);
    connect(m_protoParser, &ProtoParser::positionUpdated, this, &CommManager::positionUpdated);
    connect(m_protoParser, &ProtoParser::feedHoldPressedRemotely, this, &CommManager::feedHoldPressedRemotely);
    connect(m_protoParser, &ProtoParser::currentStepChanged, this, &CommManager::currentStepChanged);
    connect(m_protoParser, &ProtoParser::cycleStopped, this, &CommManager::cycleStopped);
}

void CommManager::dataReceived(const QByteArray &data)
{
    m_protoParser->parseMessage(data);
}
