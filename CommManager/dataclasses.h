#ifndef DATACLASSES_H
#define DATACLASSES_H

#include <QString>
/*
 *  Define all custom data types here
*/

enum COORDINATE_TYPE {X, Y, Z, ALL};
struct PositionExact {
    qint32 x;
    qint32 y;
    qint32 z;
    COORDINATE_TYPE type;

    PositionExact();
};

struct ProgramLine {
    QString commandLine;
    quint32 step;

    ProgramLine();
};

#endif // DATACLASSES_H
