#include "physical.hpp"

Physical::Physical(float x, float y,
                   std::map<std::string, sf::Texture>& textures)
    : Entity(x, y, textures) {}

const float& Physical::GetMass() { return mass_; };