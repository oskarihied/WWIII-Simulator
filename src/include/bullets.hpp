#include "bullet.hpp"

class RegularBullet : public Bullet {
 public:
  RegularBullet(float x, float y, float xVel, float yVel)
      : Bullet(0, 0, xVel, yVel, "images/bullet.png", 0.4f, 0.1f, 20, 1) {}
};