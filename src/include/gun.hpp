#ifndef GUN_HPP
#define GUN_HPP

#include "bullet.hpp"
#include "entity.hpp"

class Gun : public Entity {
 public:
  Gun(float x, float y, std::map<std::string, sf::Texture>& textures);

  std::unique_ptr<Bullet>& GetBullet();

  virtual char GunType() = 0;

 protected:
  std::unique_ptr<Bullet> bullet_ = nullptr;
};

class Rifle : public Gun {
 public:
  Rifle(float x, float y, std::map<std::string, sf::Texture>& textures);

  char GunType();
};

class RocketLauncher : public Gun {
 public:
  RocketLauncher(float x, float y,
                 std::map<std::string, sf::Texture>& textures);

  char GunType();
};

#endif