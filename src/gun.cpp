#include "gun.hpp"

Gun::Gun(float x, float y) : Entity(x, y) { SetType(EntityType::GUN); }

Gun::~Gun() {};

std::unique_ptr<Bullet>& Gun::GetBullet() { return bullet_; }

Rifle::Rifle(float x, float y) : Gun(x, y) {
  bullet_ = std::make_unique<RifleBullet>(x, y);
  SetTexture("rifle");
}

enum Gun::GunType Rifle::GunType() { return GunType::RIFLE; }

RocketLauncher::RocketLauncher(float x, float y) : Gun(x, y) {
  bullet_ = std::make_unique<Rocket>(x, y);
  SetTexture("rocket_launcher");
}

enum Gun::GunType RocketLauncher::GunType() { return GunType::LAUNCHER; }