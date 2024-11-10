#include "bullet.hpp"

#include <box2d/math_functions.h>

Bullet::Bullet(float x, float y, float xVel, float yVel, std::string image,
               float mass, int hp)
    : Rigid(x, y, xVel, yVel, image, 0.1f, 0.1f, mass, hp) {}

float Bullet::CalculateDmg() {
  float vel = sqrt(b2LengthSquared((b2Vec2){vel_.GetX(), vel_.GetY()}));
  return 0.5 * mass_ * vel * vel;
}