#ifndef COMMMANAGER_H
#define COMMMANAGER_H

#include <QObject>
#include "dataclasses.h"

class ProtoParser;

class CommManager : public QObject
{
    Q_OBJECT
public:
    static CommManager *instance();

signals:
    void positionUpdated(const PositionExact &pos);
    void feedHoldPressed(bool isPressed);
    void currentStepChanged(quint32 currentStep);
    void cycleStopped();

private:
    static CommManager *m_instance;
    ProtoParser *m_protoParser;
    explicit CommManager(QObject *parent = nullptr);

private slots:
    void dataReceived(const QByteArray &data);
};

#endif // COMMMANAGER_H
