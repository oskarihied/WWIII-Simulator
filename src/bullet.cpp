#include "bullet.hpp"

Bullet::Bullet(float x, float y, sf::Texture& texture)
    : Physical(x, y, texture) {}

RifleBullet::RifleBullet(float x, float y,
                         std::map<std::string, sf::Texture> textures)
    : Bullet(x, y, textures.at("bullet")) {
  width_ = 0.4f;
  height_ = 0.1f;
  maxHealth_ = 1;
  health_ = 1;
  mass_ = 150;
  damagedTexture_ = std::make_optional(textures.at("bullet_damaged"));
}

Rocket::Rocket(float x, float y, std::map<std::string, sf::Texture> textures)
    : Bullet(x, y, textures.at("rocket")) {
  width_ = 0.4f;
  height_ = 0.1f;
  maxHealth_ = 1;
  health_ = 1;
  mass_ = 1000;
  explodes_ = true;
}