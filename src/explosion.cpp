#include "explosion.hpp"

Explosion::Explosion(float x, float y, sf::Texture& texture1,
                     sf::Texture& texture2, sf::Texture& texture3, int count)
    : Entity(x, y, texture1),
      texture1_(texture1),
      texture2_(texture2),
      texture3_(texture3),
      count_(count) {}

int Explosion::GetCount() { return count_; }

void Explosion::NextSprite() {
  count_++;

  if (count_ == 4) {
    ChangeTexture(texture2_);
  }

  if (count_ == 8) {
    ChangeTexture(texture3_);
  }
}