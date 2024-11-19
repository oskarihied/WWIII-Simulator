#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "rigid.hpp"

class Enemy : public Rigid {
 public:
  Enemy(float x, float y, sf::Texture& texture, float mass, int hp, int dur);
};

#endif