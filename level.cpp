#include "level.h"
Level::Level() : sizeX(GameSettings::LEVEL_XDIM), sizeY(GameSettings::LEVEL_YDIM)
{
    //Get random position, exclude where snake is, snake is spawned in the middle
    Position randomPos(Position::GetRandomPositionWithLimits(sizeX, sizeY));
    while (randomPos == GetLevelCenter())
    {
        randomPos = Position::GetRandomPositionWithLimits(sizeX, sizeY);
    }
    fruit = new Apple(new Position(randomPos));
}
void Level::SpawnNewFruit(Snake &snake)
{
    //Get random position
    Position spawnPos = Position::GetRandomPositionWithLimits(sizeX, sizeY);
    bool freeTile = false;
    //Check if position is distinct from where the snake is
    while (!freeTile)
    {
        if (!(spawnPos == snake.GetPosition()))
        {
            Tail *tailptr = snake.GetTail();
            for (size_t i = 0; tailptr != NULL; i++)
            {
                if (!(spawnPos == *tailptr->position))
                {
                    tailptr = tailptr->nextTail;
                }
                else
                {
                    spawnPos = Position::GetRandomPositionWithLimits(sizeX, sizeY);
                    break;
                }
            }
            if (tailptr == NULL)
            {
                freeTile = true;
            }
        }
        else
        {
            spawnPos = Position::GetRandomPositionWithLimits(sizeX, sizeY);
        }
    }
    //std::cout << "SPAWN\n";
    delete fruit;
    //Spawn new fruit
    fruit = new Apple(new Position(spawnPos));
}
Fruit &Level::GetFruit() { return *fruit; }
Position Level::GetLevelCenter()
{
    {
        int centerX = ((GameSettings::LEVEL_XDIM - 1) / 2);
        int centerY = ((GameSettings::LEVEL_YDIM - 1) / 2);
        return Position(centerX, centerY);
    }
}
Level::~Level() { delete fruit; }