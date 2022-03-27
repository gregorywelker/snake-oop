#ifndef APPLE_H
#define APPLE_H
#include <iostream>
#include "fruit.h"
// #include "memtrace.h"
class Apple : public Fruit
{
public:
    Apple(const Position *pos);
    void EatenBy(Snake &snake);
    ~Apple();
};

#endif