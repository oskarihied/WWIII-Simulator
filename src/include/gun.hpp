#ifndef GUN_HPP
#define GUN_HPP

#include "bullet.hpp"
#include "entity.hpp"

class Gun : public Entity {
 public:
  enum class GunType { RIFLE, LAUNCHER };

  Gun(float x, float y);

  virtual ~Gun() = 0;

  std::unique_ptr<Bullet>& GetBullet();

  virtual enum GunType GunType() = 0;

 protected:
  std::unique_ptr<Bullet> bullet_ = nullptr;
};

class Rifle : public Gun {
 public:
  Rifle(float x, float y);

  enum GunType GunType();
};

class RocketLauncher : public Gun {
 public:
  RocketLauncher(float x, float y);

  enum GunType GunType();
};

#endif