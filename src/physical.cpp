#include "physical.hpp"

Physical::Physical(float x, float y, sf::Texture& texture, float mass,
                   float width, float height)
    : Entity(x, y, texture), mass_(mass), width_(width), height_(height) {};

void Physical::UpdateDims(float w, float h) {
  width_ = w;
  height_ = h;
}

float Physical::GetWidth() { return width_; };

float Physical::GetHeight() { return height_; };

float Physical::GetMass() { return mass_; };