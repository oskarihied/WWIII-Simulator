#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "physical.hpp"

//Enemy that you need to destroy in order to win
class Enemy : public Physical {
 public:
  //params: x and y coordinates
  Enemy(float x, float y);

  //Change texture when damaged
  void BecomeDamaged() override;

  //enemies are dynamic
  //returns: true
  const bool IsDynamic() override;
};

#endif