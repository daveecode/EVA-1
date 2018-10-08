#ifndef COORDINATE_H
#define COORDINATE_H

struct Coordinate {

public:

    Coordinate() : x(0), y(0) {}

    Coordinate(int _x, int _y) : x(_x), y(_y) {}


    int x, y;
    bool isSet;
};
#endif // COORDINATE_H
