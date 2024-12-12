#include "ground.hpp"

Ground::Ground(float x, float y) : Physical(x, y) {
  width_ = 10.0f;
  height_ = 2.0f;
  SetType(EntityType::GROUND);
  SetTexture("ground");
}

const bool Ground::IsDynamic() { return false; }

GroundBox::GroundBox(float x, float y) : Physical(x, y) {
  width_ = 1.0f;
  height_ = 1.0f;
  SetTexture("ground_box");
}

const bool GroundBox::IsDynamic() { return false; }