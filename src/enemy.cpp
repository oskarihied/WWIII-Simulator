#include "enemy.hpp"

Enemy::Enemy(float x, float y, std::map<std::string, sf::Texture> textures)
    : Rigid(x, y, textures.at("enemy"), 100, 1) {}