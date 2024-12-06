#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "physical.hpp"

class Enemy : public Physical {
 public:
  Enemy(float x, float y, std::map<std::string, sf::Texture>& textures);
};

#endif