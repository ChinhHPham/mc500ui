#ifndef PROTOPARSER_H
#define PROTOPARSER_H
#include "Protos/mc500ipc.pb.h"
#include "dataclasses.h"

#include <QByteArray>
#include <QObject>

class ProtoParser : public QObject
{
    Q_OBJECT
public:
    explicit ProtoParser(QObject *parent = nullptr);
    void parseMessage(const QByteArray &data);
    QByteArray serializePositionUpdate(const PositionExact &pos);
    QByteArray serializeCycleStart();
    QByteArray serializeCycleStop();
    QByteArray serializeFeedHoldMessage(bool status);
    QByteArray serializeClearProgram();
    QByteArray serializeAddProgramLine(const ProgramLine &pLine);

signals:
    void positionUpdated(const PositionExact &pos);
    void feedHoldPressedRemotely(bool isPressed);
    void currentStepChanged(quint32 currentStep);
    void cycleStopped();

private:
    QByteArray serializeToArray(const mc500ipc::Message &message);
    bool parseFromArray(mc500ipc::Message &message, const QByteArray &array);
    PositionExact parsePosition(const mc500ipc::PositionUpdate &posUpdate);
};

#endif // PROTOPARSER_H
