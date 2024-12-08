#include "ground.hpp"

Ground::Ground(float x, float y, std::map<std::string, sf::Texture>& textures)
    : Physical(x, y, textures) {
  width_ = 10.0f;
  height_ = 2.0f;
  SetType(EntityType::GROUND);
  SetTexture("ground");
}