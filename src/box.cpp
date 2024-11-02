#include "box.hpp"

Box::Box(float x, float y)
    : Rigid(x, y), durability_(1) {}

Box::Box(float x, float y, float mass, int hp, int dur)
    : Rigid(x, y, mass, hp), durability_(dur) {}