#ifndef COMMMANAGER_H
#define COMMMANAGER_H

#include <QObject>
#include "dataclasses.h"

#define COMM_MANAGER CommManager::instance()
class ProtoParser;

class CommManager : public QObject
{
    Q_OBJECT
public:
    static CommManager *instance();
    void initTCPConnection();
    bool updatePosition(const PositionExact &pos);
    bool updateFeedHoldStatus(bool isPressed);
    bool cycleStart();
    bool clearProgram();
    bool addProgramLine(const ProgramLine &pLine);

signals:
    void positionUpdated(const PositionExact &pos);
    void feedHoldPressedRemotely(bool isPressed);
    void currentStepChanged(quint32 currentStep);
    void cycleStopped();
    void connectedToHost();
    void disconnectedToHost();
    void cannotEstablishConnection();

private:
    static CommManager *m_instance;
    ProtoParser *m_protoParser;
    explicit CommManager(QObject *parent = nullptr);

private slots:
    void dataReceived(const QByteArray &data);

};

#endif // COMMMANAGER_H
