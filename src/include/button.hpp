#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "entity.hpp"

class Button : public Entity {
 public:
  Button(float x, float y, float w, float h, const std::string textureName);

  bool IsTouching(float x, float y);
};

#endif