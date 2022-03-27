#ifndef FRUIT_H
#define FRUIT_H
#include "position.h"
// #include "memtrace.h"
class Snake;
class Fruit
{
    const char *name;
    const Position *position;

public:
    Fruit(const char *name, const Position *pos);
    //const char *GetName();
    virtual void EatenBy(Snake &snake) = 0;
    const Position &GetPos();
    virtual ~Fruit();
};
#include "snake.h"
#endif