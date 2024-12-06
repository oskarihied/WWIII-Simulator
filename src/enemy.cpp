#include "enemy.hpp"

Enemy::Enemy(float x, float y, std::map<std::string, sf::Texture>& textures)
    : Physical(x, y, textures) {
  mass_ = 100;
  maxHealth_ = 1000;
  health_ = 1000;
  points_ = 1000;
  SetType(Entity::EntityType::ENEMY);
  SetTexture("enemy");
}

void Enemy::BecomeDamaged() {
  if (health_ < maxHealth_ * 0.9f) {
    SetTexture("enemy_damaged");
  }
}