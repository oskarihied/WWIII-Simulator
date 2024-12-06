#include "bullet.hpp"

Bullet::Bullet(float x, float y, std::map<std::string, sf::Texture>& textures)
    : Physical(x, y, textures) {
  SetType(Entity::EntityType::BULLET);
}

RifleBullet::RifleBullet(float x, float y,
                         std::map<std::string, sf::Texture>& textures)
    : Bullet(x, y, textures) {
  width_ = 0.4f;
  height_ = 0.1f;
  maxHealth_ = 1;
  health_ = 1;
  mass_ = 150;
  SetTexture("bullet");
}

void RifleBullet::BecomeDamaged() {
  if (health_ < maxHealth_ * 0.9f) {
    SetTexture("bullet_damaged");
  }
}

Rocket::Rocket(float x, float y, std::map<std::string, sf::Texture>& textures)
    : Bullet(x, y, textures) {
  width_ = 0.4f;
  height_ = 0.1f;
  maxHealth_ = 1;
  health_ = 1;
  mass_ = 1000;
  explodes_ = true;
  SetTexture("rocket");
}