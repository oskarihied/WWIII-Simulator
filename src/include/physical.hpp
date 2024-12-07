#ifndef PHYSICAL_HPP
#define PHYSICAL_HPP

#include "entity.hpp"

class Physical : public Entity {
 public:
  Physical(float x, float y, std::map<std::string, sf::Texture>& textures);

  const float& GetWidth();
  const float& GetHeight();
  const float& GetMass();

 protected:
  float width_ = 1.0f;
  float height_ = 1.0f;
  float mass_;
};

#endif