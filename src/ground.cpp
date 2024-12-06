#include "ground.hpp"

Ground::Ground(float x, float y, std::map<std::string, sf::Texture>& textures)
    : Physical(x, y, textures) {
  width_ = 10.0f;
  height_ = 10.0f;
  mass_ = 100.0f;
  SetType(Entity::EntityType::GROUND);
  SetTexture("ground");
}