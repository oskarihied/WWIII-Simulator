#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "entity.hpp"

class Button : public Entity {
 public:
  Button(float x, float y, float sizeX, float sizeY,
         const std::string textureName,
         std::map<std::string, sf::Texture>& textures);

  bool IsTouching(float x, float y);

 private:
  Vector pos_;

  float sizeX_;
  float sizeY_;
};

#endif