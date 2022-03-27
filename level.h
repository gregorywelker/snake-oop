#ifndef LEVEL_H
#define LEVEL_H
#include "position.h"
#include <iostream>
#include "apple.h"
#include "gameSettings.h"
// #include "memtrace.h"
class Snake;
class Level
{
    //Level size can be changed in gameSettings.h
    int sizeX, sizeY;
    //Multiple fruits could be spawned on the level
    Fruit *fruit;

public:
    Level();
    static Position GetLevelCenter();
    void SpawnNewFruit(Snake &snake);
    Fruit &GetFruit();
    void Draw();
    ~Level();
};
#include "snake.h"
#endif