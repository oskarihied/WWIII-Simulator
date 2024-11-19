#include "enemy.hpp"

Enemy::Enemy(float x, float y, sf::Texture& texture, float mass, int hp, int dur)
    : Rigid(x, y, texture, mass, hp) {}