#ifndef BULLET_HPP
#define BULLET_HPP

#include "physical.hpp"

//Shot from a Gun. Deals damage to Boxes and Enemies
class Bullet : public Physical {
 public:
  //params: Bullets x and y coordinates
  Bullet(float x, float y);

  //Bullets are dynamic
  //returns true
  const bool IsDynamic() override;
};

//Bullet of a Rifle
class RifleBullet : public Bullet {
 public:
  RifleBullet(float x, float y);

  //Changing Bullet texture when damaged
  void BecomeDamaged() override;
};

//Bullet of a Rocket Launcher
class Rocket : public Bullet {
 public:
  Rocket(float x, float y);
};

#endif