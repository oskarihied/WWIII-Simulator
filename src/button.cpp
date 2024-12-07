#include "button.hpp"

Button::Button(float x, float y, float sizeX, float sizeY,
               const std::string textureName,
               std::map<std::string, sf::Texture>& textures)
    : Entity(x, y, textures), sizeX_(sizeX), sizeY_(sizeY) {
  pos_ = Vector(x, y);
  SetTexture(textureName);
}

bool Button::IsTouching(float x, float y) {
  bool xOK =
      (x >= pos_.GetX() - sizeX_ / 2.0) && (x <= pos_.GetX() + sizeX_ / 2.0);
  bool yOK =
      (y >= pos_.GetY() - sizeY_ / 2.0) && (y <= pos_.GetY() + sizeY_ / 2.0);
  return (xOK && yOK);
}