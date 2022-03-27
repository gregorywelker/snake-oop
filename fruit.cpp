#include "fruit.h"

Fruit::Fruit(const char *name, const Position *pos) : name(name), position(pos) {}
//const char *Fruit::GetName() { return name; }
const Position &Fruit::GetPos() { return *position; }
Fruit::~Fruit() { delete position; }