#ifndef DATACLASSES_H
#define DATACLASSES_H

enum COORDINATE_TYPE {X, Y, Z, ALL};
struct PositionExact {
    int x;
    int y;
    int z;
    COORDINATE_TYPE type;

    PositionExact();
};

#endif // DATACLASSES_H
