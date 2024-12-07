#ifndef GROUND_HPP
#define GROUND_HPP

#include "physical.hpp"

class Ground : public Physical {
 public:
  Ground(float x, float y, std::map<std::string, sf::Texture>& textures);
};

#endif