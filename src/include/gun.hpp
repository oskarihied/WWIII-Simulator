#ifndef GUN_HPP
#define GUN_HPP

#include "bullet.hpp"
#include "entity.hpp"

class Gun : public Entity {
 public:
  Gun(float x, float y, sf::Texture& texture, Bullet* bullet);

  Bullet* GetBullet();

  virtual char GetType() = 0;

 private:
  Bullet* bullet_;
};

class Rifle : public Gun {
 public:
  Rifle(float x, float y, std::map<std::string, sf::Texture> textures)
      : Gun(x, y, textures.at("rifle"), new RifleBullet(x, y, textures)) {}

  char GetType() { return 'A'; }
};

class RocketLauncher : public Gun {
 public:
  RocketLauncher(float x, float y, std::map<std::string, sf::Texture> textures)
      : Gun(x, y, textures.at("rocket_launcher"), new Rocket(x, y, textures)) {}

  char GetType() { return 'R'; }
};

#endif