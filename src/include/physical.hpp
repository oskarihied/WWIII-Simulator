#ifndef PHYSICAL_HPP
#define PHYSICAL_HPP

#include "entity.hpp"

class Physical : public Entity {
 public:
  Physical(float x, float y, std::map<std::string, sf::Texture>& textures);

  const float& GetMass();

 protected:
  float mass_;
};

#endif