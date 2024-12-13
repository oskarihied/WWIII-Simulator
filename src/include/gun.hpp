#ifndef GUN_HPP
#define GUN_HPP

#include "bullet.hpp"
#include "entity.hpp"

//Represents different types of guns in the game
class Gun : public Entity {
 public:
  //Guns type
  enum class GunType { RIFLE, LAUNCHER };

  //params: x and y coordinates
  Gun(float x, float y);

  //virtual destructor
  virtual ~Gun() = 0;

  //returns: the bullet associated with the gun
  std::unique_ptr<Bullet>& GetBullet();

  //returns: guns type
  virtual enum GunType GunType() = 0;

 protected:
  //gun's bullet
  std::unique_ptr<Bullet> bullet_ = nullptr;
};

//Rifle, shoots normal bullets
class Rifle : public Gun {
 public:
  Rifle(float x, float y);

  enum GunType GunType();
};

//Rocket Launcher, shoots explosive rockets
class RocketLauncher : public Gun {
 public:
  RocketLauncher(float x, float y);

  enum GunType GunType();
};

#endif