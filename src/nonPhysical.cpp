#include "nonPhysical.hpp"

NonPhysical::NonPhysical(float x, float y) 
    : Entity(x, y) {};

NonPhysical::NonPhysical(float x, float y, std::string image) 
    : Entity(x, y, image) {};