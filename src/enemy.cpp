#include "enemy.hpp"

Enemy::Enemy(float x, float y) : Physical(x, y) {
  mass_ = 10;
  maxHealth_ = 1000;
  health_ = 1000;
  points_ = 1000;
  sound_ = "death";
  SetType(EntityType::ENEMY);
  SetTexture("enemy");
}

void Enemy::BecomeDamaged() {
  if (health_ < maxHealth_ * 0.9f) {
    SetTexture("enemy_damaged");
  }
}

const bool Enemy::IsDynamic() { return true; }