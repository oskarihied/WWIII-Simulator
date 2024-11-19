#include "enemy.hpp"

Enemy::Enemy(float x, float y, sf::Texture texture)
    : Rigid(x, y, texture, 100, 10) {}