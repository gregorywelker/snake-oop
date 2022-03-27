#include "position.h"

Position::Position(int posX, int posY) : x(posX), y(posY) {}
Position::Position(const Position &pos) : x(pos.x), y(pos.y) {}
bool Position::operator==(const Position &pos) const
{
    if (x == pos.x && y == pos.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void Position::operator=(const Position &pos)
{
    this->x = pos.x;
    this->y = pos.y;
}
Position Position::GetRandomPositionWithLimits(int limX, int limY)
{
    int randX = rand() % limX;
    int randY = rand() % limY;
    return Position(randX, randY);
}
Position::~Position() {}
std::ostream &operator<<(std::ostream &os, const Position &pos)
{
    os << pos.x << " " << pos.y;
    return os;
}