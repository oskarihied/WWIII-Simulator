#ifndef BULLET_HPP
#define BULLET_HPP

#include "rigid.hpp"

class Bullet : public Rigid {
 public:
  Bullet(float x, float y, float xVel, float yVel, std::string image, float w,
         float h, float mass, int hp);

  float CalculateDmg();
};

#endif