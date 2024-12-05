#include "bullet.hpp"

Bullet::Bullet(float x, float y, sf::Texture& texture, float mass, int hp)
    : Rigid(x, y, texture, mass, hp) {}

RifleBullet::RifleBullet(float x, float y,
                         std::map<std::string, sf::Texture> textures)
    : Bullet(x, y, textures.at("bullet"), 1000, 1) {
  damaged_ = std::make_optional(textures.at("bullet_damaged"));
}

Rocket::Rocket(float x, float y, std::map<std::string, sf::Texture> textures)
    : Bullet(x, y, textures.at("rocket"), 1000, 1) {
  explode_ = true;
}