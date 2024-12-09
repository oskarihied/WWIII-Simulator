#ifndef BULLET_HPP
#define BULLET_HPP

#include "physical.hpp"

class Bullet : public Physical {
 public:
  Bullet(float x, float y);
};

class RifleBullet : public Bullet {
 public:
  RifleBullet(float x, float y);

  void BecomeDamaged() override;
};

class Rocket : public Bullet {
 public:
  Rocket(float x, float y);
};

#endif