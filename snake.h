#ifndef SNAKE_H
#define SNAKE_H
#include "position.h"
#include "gameSettings.h"
#include "level.h"
#include "fruit.h"
// #include "memtrace.h"
struct Tail
{
    Position *position;
    Tail *nextTail;

    Tail(Position *pos);
    ~Tail();
};
typedef enum Direction
{
    LEFT = -2,
    UP = -1,
    DOWN = 1,
    RIGHT = 2,
} Direction;
class Snake
{
    int length;
    Position *headPos;
    Tail *tail;
    Direction direction;
    bool isDead;
    void CheckSelfEat();

public:
    Snake();
    void Step();
    void SetDirection(Direction dir);
    void Eat(Fruit &fruit);
    Position &GetPosition();
    Tail *GetTail();
    bool GetIsDead();
    const char *GetDirectionText();
    Direction GetDirection();
    int GetLength();
    void Grow();
    //void Draw();
    ~Snake();
};

#endif