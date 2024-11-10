#include "bullet.hpp"

class RegularBullet : public Bullet {
 public:
  RegularBullet(float x, float y, float xVel, float yVel)
      : Bullet(x, y, xVel, yVel, "images/bullet.png", 20, 1) {}
};