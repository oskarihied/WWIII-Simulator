#ifndef NONPHYSICAL_HPP
#define NONPHYSICAL_HPP

#include "entity.hpp"

class NonPhysical : public Entity {
 public:
  NonPhysical(float x, float y, sf::Texture& texture);
};

#endif