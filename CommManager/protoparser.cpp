#include "protoparser.h"
#include "tcpsocket.h"

ProtoParser::ProtoParser(QObject *parent)
{
}

bool ProtoParser::parseFromArray(mc500ipc::Message &message, const QByteArray &array)
{
    qDebug() << "Parsing: " << array;
    if (!array.isEmpty() && !message.ParseFromArray(array.constData(), array.size())) {
        return false;
    }
    return true;
}

QByteArray ProtoParser::serializePositionUpdate(const PositionExact &pos)
{
    mc500ipc::Message message;
    mc500ipc::SetWorkCoordinates *update(message.mutable_setworkcoordinates());
    mc500ipc::Coordinate *coordinate(update->mutable_currentworkcoordinate());
    switch (pos.type) {
    case X:
        coordinate->set_x(pos.x);
        break;
    case Y:
        coordinate->set_y(pos.y);
        break;
    case Z:
        coordinate->set_z(pos.z);
        break;
    case ALL:
        coordinate->set_x(pos.x);
        coordinate->set_y(pos.y);
        coordinate->set_z(pos.z);
        break;
    default:
        break;
    }
    return serializeToArray(message);
}

QByteArray ProtoParser::serializeCycleStop()
{
    mc500ipc::Message message;
    message.mutable_cyclestop();
    return serializeToArray(message);
}

QByteArray ProtoParser::serializeCycleStart()
{
    mc500ipc::Message message;
    message.mutable_cyclestart();
    return serializeToArray(message);
}

QByteArray ProtoParser::serializeFeedHoldMessage(bool status)
{
    mc500ipc::Message message;
    if (status) {
        message.mutable_feedholdpressed();
    } else {
        message.mutable_feedholdreleased();
    }
    return serializeToArray(message);
}

QByteArray ProtoParser::serializeClearProgram()
{
    mc500ipc::Message message;
    message.mutable_clearprogram();
    return serializeToArray(message);
}

QByteArray ProtoParser::serializeAddProgramLine(const ProgramLine &pLine)
{
    mc500ipc::Message message;
    mc500ipc::AddProgramLine *addLine(message.mutable_addprogramline());
    addLine->set_code(pLine.commandLine.toStdString());
    addLine->set_step(pLine.step);
    return serializeToArray(message);
}

QByteArray ProtoParser::serializeToArray(const mc500ipc::Message &message)
{
    QByteArray protoValue(message.ByteSizeLong(), Qt::Uninitialized);
    if (!message.SerializeToArray(protoValue.data(), protoValue.size())) {
        qDebug() << QStringLiteral("Could not serialize ") << QString::fromStdString(message.GetTypeName());
        Q_ASSERT(false);
    }
    return protoValue;
}

PositionExact ProtoParser::parsePosition(const mc500ipc::PositionUpdate &posUpdate)
{
    const ::mc500ipc::Coordinate &currentCoordinate = posUpdate.currentworkcoordinate();
    PositionExact pos;
    bool allCoordinate = currentCoordinate.has_x() && currentCoordinate.has_y() && currentCoordinate.has_z();
    if (allCoordinate) {
        pos.x = currentCoordinate.x();
        pos.y = currentCoordinate.y();
        pos.z = currentCoordinate.z();
        pos.type = COORDINATE_TYPE::ALL;
    } else if (currentCoordinate.has_x()) {
        pos.x = currentCoordinate.x();
        pos.type = COORDINATE_TYPE::X;
    } else if (currentCoordinate.has_y()) {
        pos.y = currentCoordinate.y();
        pos.type = COORDINATE_TYPE::Y;
    } else if (currentCoordinate.has_z()) {
        pos.z = currentCoordinate.z();
        pos.type = COORDINATE_TYPE::Z;
    }
    return pos;
}

void ProtoParser::parseMessage(const QByteArray &data)
{
    mc500ipc::Message message;
    if (!parseFromArray(message, data)) {
        qDebug() << QStringLiteral("Cannot parse data ") << data.data();
    }

    //Parse position update
    if (message.has_positionupdate()){
        emit positionUpdated(parsePosition(message.positionupdate()));
    }

    //Parse feed hold message
    if (message.has_feedholdpressed()) {
        emit feedHoldPressedRemotely(true);
    } else if (message.has_feedholdreleased()) {
        emit feedHoldPressedRemotely(false);
    }

    //Parse Cycle executing step
    if (message.has_cycleexecuting()) {
        emit currentStepChanged(message.cycleexecuting().currentprogramstep());
    }

    //Parse Cycle stopped
    if (message.has_cyclestopped()) {
        emit cycleStopped();
    }
}
