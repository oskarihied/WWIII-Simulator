#include <box2d/box2d.h>

#include "rigid.hpp"

class Bullet : public Rigid {
 public:
  Bullet(float x, float y, float xVel, float yVel, std::string image,
         float mass, int hp);

  float CalculateDmg();
};