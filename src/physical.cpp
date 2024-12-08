#include "physical.hpp"

Physical::Physical(float x, float y) : Entity(x, y) {}

const float& Physical::GetMass() { return mass_; };