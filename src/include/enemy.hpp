#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "rigid.hpp"

class Enemy : public Rigid {
 public:
  Enemy(float x, float y, std::map<std::string, sf::Texture> textures);
};

#endif