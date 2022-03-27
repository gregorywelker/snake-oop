#include "apple.h"
Apple::Apple(const Position *pos) : Fruit("Apple", pos) {}

void Apple::EatenBy(Snake &snake)
{
    //std::cout << "Snake is eating me\n";
    snake.Grow();
}
Apple::~Apple() {}