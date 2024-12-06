#include "enemy.hpp"

Enemy::Enemy(float x, float y, std::map<std::string, sf::Texture>& textures)
    : Physical(x, y, textures.at("enemy")) {
  mass_ = 100;
  maxHealth_ = 1000;
  health_ = 1000;
  damagedTexture_ = std::make_optional(textures.at("enemy_damaged"));
  points_ = 1000;
}