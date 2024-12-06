#ifndef PHYSICAL_HPP
#define PHYSICAL_HPP

#include "entity.hpp"

class Physical : public Entity {
 public:
  Physical(float x, float y, sf::Texture& texture);

  void SetDims(float w, float h);
  void SetMass(float m);
  void SetToMaxHealth(float hp);

  const float& GetWidth();
  const float& GetHeight();
  const float& GetMass();

 protected:
  float width_ = 1.0f;
  float height_ = 1.0f;
  float mass_;
};

#endif