#ifndef COORDINATE_H
#define COORDINATE_H


struct Coordinate {

public:

    Coordinate() : x(0), y(0), isQueen(false) {}
    Coordinate(int _x, int _y, bool l) : x(_x), y(_y), isQueen(l) {}

    int x, y;
    bool isQueen;
};

#endif // COORDINATE_H
