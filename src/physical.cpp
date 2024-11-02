#include "physical.hpp"

Physical::Physical(float x, float y) 
    : Entity(x, y), mass_(1) {};

Physical::Physical(float x, float y, float mass) 
    : Entity(x, y), mass_(mass) {};