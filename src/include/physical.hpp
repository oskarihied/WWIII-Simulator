#ifndef PHYSICAL_HPP
#define PHYSICAL_HPP

#include "entity.hpp"

class Physical : public Entity {
 public:
  Physical(float x, float y, sf::Texture& texture, float mass, float width,
           float height);

  void UpdateDims(float w, float h);

  float GetWidth();
  float GetHeight();

 protected:
  float mass_;
  float width_;
  float height_;
};

#endif