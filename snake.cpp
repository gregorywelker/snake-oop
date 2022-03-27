#include "snake.h"

Tail::Tail(Position *pos) : position(pos), nextTail(NULL) {}
Tail::~Tail()
{
    delete position;
}

Snake::Snake() : length(1), tail(NULL), direction(LEFT), isDead(false)
{
    headPos = new Position(Level::GetLevelCenter());
};

void Snake::Step()
{
    //Step all the tail parts
    if (tail != NULL)
    {
        Position prevPos(*tail->position);
        *tail->position = *headPos;
        //std::cout << "Tail 0: " << *tail->position << "\t";
        Tail *tailPtr = tail->nextTail;
        for (size_t i = 0; tailPtr != NULL; i++)
        {
            Position temp = *tailPtr->position;
            *tailPtr->position = prevPos;
            //std::cout << "Tail " << i + 1 << ": " << *tailPtr->position << "\t";
            prevPos = temp;
            tailPtr = tailPtr->nextTail;
        }
    }
    //Step head, if head is over level limits, new position is at the other side of the given axis
    headPos->x += direction / 2;
    headPos->y += direction % 2;
    if (headPos->x < 0)
    {
        headPos->x = GameSettings::LEVEL_XDIM - 1;
    }
    else if (headPos->x >= GameSettings::LEVEL_XDIM)
    {
        headPos->x = 0;
    }
    if (headPos->y < 0)
    {
        headPos->y = GameSettings::LEVEL_YDIM - 1;
    }
    else if (headPos->y >= GameSettings::LEVEL_YDIM)
    {
        headPos->y = 0;
    }
    CheckSelfEat();
    //std::cout << "Head: " << *headPos << "\n";
}

//Check every tail part whether it's position is equal to the head's position
void Snake::CheckSelfEat()
{
    Tail *tailptr = tail;
    for (size_t i = 0; tailptr != NULL; i++)
    {
        if (*headPos == *tailptr->position)
        {
            isDead = true;
            break;
        }
        else
        {
            tailptr = tailptr->nextTail;
        }
    }
}
void Snake::Eat(Fruit &fruit)
{
    fruit.EatenBy(*this);
}
Position &Snake::GetPosition()
{
    return *headPos;
}

//Add a new tail part at the and of the snake
void Snake::Grow()
{
    length++;
    //std::cout << "GROW: " << length << "\n";
    if (tail == NULL)
    {
        tail = new Tail(new Position(*headPos));
    }
    else
    {
        Tail *tailPtr = tail;
        for (size_t i = 0; tailPtr->nextTail != NULL; i++)
        {
            tailPtr = tailPtr->nextTail;
        }
        tailPtr->nextTail = new Tail(new Position(*tailPtr->position));
    }
}
// void Snake::Draw()
// {
//     system("clear");
//     for (int i = 0; i < GameSettings::LEVEL_YDIM; i++)
//     {
//         for (int j = 0; j < GameSettings::LEVEL_XDIM; j++)
//         {
//             bool drawn = false;
//             if (*headPos == Position(j, i))
//             {
//                 drawn = true;
//                 std::cout << "X";
//             }
//             Tail *tailptr = tail;
//             for (int m = 0; tailptr != NULL; m++)
//             {
//                 if (*tailptr->position == Position(j, i))
//                 {
//                     std::cout << "0";
//                     drawn = true;
//                     break;
//                 }
//                 tailptr = tailptr->nextTail;
//             }
//             if (!drawn)
//             {
//                 std::cout << ".";
//             }
//         }
//         std::cout << std::endl;
//     }
// }
Tail *Snake::GetTail()
{
    return tail;
}
bool Snake::GetIsDead()
{
    return isDead;
}
int Snake::GetLength()
{
    return length;
}
const char *Snake::GetDirectionText()
{
    switch (direction)
    {
    case -2:
        return "BAL";
    case -1:
        return "FEL";
    case 1:
        return "LE";
    default:
        return "JOBB";
    }
}
Direction Snake::GetDirection()
{
    return direction;
}
void Snake::SetDirection(Direction dir) { direction = dir; }
Snake::~Snake()
{
    delete headPos;
    //Delete linked list
    Tail *tailPtr = tail;
    for (size_t i = 0; tailPtr != NULL; i++)
    {
        Tail *tempPtr = tailPtr->nextTail;
        delete tailPtr;
        tailPtr = tempPtr;
    }
}
