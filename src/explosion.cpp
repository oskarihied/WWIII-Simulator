#include "explosion.hpp"

Explosion::Explosion(float x, float y,
                     std::map<std::string, sf::Texture>& textures)
    : Entity(x, y, textures) {
  SetTexture("explosion1");
}

const int& Explosion::GetCount() const { return count_; }

void Explosion::NextSprite() {
  count_++;
  if (count_ == 4) {
    SetTexture("explosion2");
  } else if (count_ == 8) {
    SetTexture("explosion3");
  }
}