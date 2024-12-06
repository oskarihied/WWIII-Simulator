#include "physical.hpp"

Physical::Physical(float x, float y, sf::Texture& texture)
    : Entity(x, y, texture) {};

void Physical::SetDims(float w, float h) {
  width_ = w;
  height_ = h;
}

void Physical::SetMass(float m) { mass_ = m; }

void Physical::SetToMaxHealth(float hp) {
  maxHealth_ = hp;
  health_ = hp;
}

const float& Physical::GetWidth() { return width_; };

const float& Physical::GetHeight() { return height_; };

const float& Physical::GetMass() { return mass_; };