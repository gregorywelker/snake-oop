#ifndef POSITION_H
#define POSITION_H
#include <iostream>
#include <math.h>
// #include "memtrace.h"
struct Position
{
    int x, y;
    //Constructor
    Position(int posX, int posY);
    //Copy constructor
    Position(const Position &pos);
    //Equal check
    bool operator==(const Position &pos) const;
    void operator=(const Position &pos);
    //Fucntion for random position
    static Position GetRandomPositionWithLimits(int limX, int limY);
    ~Position();
};
std::ostream &operator<<(std::ostream &os, const Position &pos);
#endif