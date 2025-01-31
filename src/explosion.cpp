#include "explosion.hpp"

Explosion::Explosion(float x, float y) : Entity(x, y) {
  SetType(EntityType::EXPLOSION);
  SetTexture("explosion1");
}

const int& Explosion::GetCount() const { return count_; }

void Explosion::NextSprite() {
  //changes texture based on the count
  count_++;
  if (count_ == 4) {
    SetTexture("explosion2");
  } else if (count_ == 8) {
    SetTexture("explosion3");
  }
}