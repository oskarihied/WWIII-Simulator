#include "ground.hpp"

Ground::Ground(float x, float y, sf::Texture& texture)
    : Physical(x, y, texture) {
  width_ = 10.0f;
  height_ = 10.0f;
  mass_ = 100.0f;
}