#include "bullet.hpp"

#include <box2cpp/box2cpp.h>

Bullet::Bullet(float x, float y, float xVel, float yVel, std::string image,
               float w, float h, float mass, int hp)
    : Rigid(x, y, xVel, yVel, image, w, h, mass, hp) {}

Bullet::Bullet(float x, float y, float xVel, float yVel, sf::Texture& texture,
               float w, float h, float mass, int hp)
    : Rigid(x, y, xVel, yVel, texture, w, h, mass, hp) {}

float Bullet::CalculateDmg() {
  float vel = sqrt(b2LengthSquared((b2Vec2){vel_.GetX(), vel_.GetY()}));
  return 0.5 * mass_ * vel * vel;
}


RegularBullet::RegularBullet(float x, float y, float xVel, float yVel)
    : Bullet(0, 0, xVel, yVel, "images/bullet.png", 0.4f, 0.1f, 20, 1) {
    }

RifleBullet::RifleBullet(float x, float y, std::map<std::string, sf::Texture> textures) 
    : Bullet(x, y, 0, 0, textures.at("bullet"), 0.4f, 0.1f, 1000, 1) {
      damaged_ = std::make_optional(textures.at("bullet_damaged"));
    }

Rocket::Rocket(float x, float y, std::map<std::string, sf::Texture> textures) 
    : Bullet(x, y, 0, 0, textures.at("rocket"), 0.4f, 0.1f, 1000, 1) {
      explode_ = true;
    }