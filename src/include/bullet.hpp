#ifndef BULLET_HPP
#define BULLET_HPP

#include "rigid.hpp"

class Bullet : public Rigid {
 public:
  Bullet(float x, float y, sf::Texture& texture, float mass, int hp);
};

class RifleBullet : public Bullet {
 public:
  RifleBullet(float x, float y, std::map<std::string, sf::Texture> textures);
};

class Rocket : public Bullet {
 public:
  Rocket(float x, float y, std::map<std::string, sf::Texture> textures);
};

#endif