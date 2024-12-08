#include "button.hpp"

Button::Button(float x, float y, float w, float h,
               const std::string textureName)
    : Entity(x, y) {
  width_ = w;
  height_ = h;
  SetTexture(textureName);
}

bool Button::IsTouching(float x, float y) {
  bool xOK =
      (x >= pos_.GetX() - width_ / 2.0) && (x <= pos_.GetX() + width_ / 2.0);
  bool yOK =
      (y >= pos_.GetY() - height_ / 2.0) && (y <= pos_.GetY() + height_ / 2.0);
  return (xOK && yOK);
}