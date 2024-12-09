#include "ground.hpp"

Ground::Ground(float x, float y) : Physical(x, y) {
  width_ = 10.0f;
  height_ = 2.0f;
  SetType(EntityType::GROUND);
  SetTexture("ground");
}