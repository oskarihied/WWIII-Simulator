#include "gun.hpp"

Gun::Gun(float x, float y, std::map<std::string, sf::Texture>& textures)
    : Entity(x, y, textures) {}

std::unique_ptr<Bullet>& Gun::GetBullet() { return bullet_; }

Rifle::Rifle(float x, float y, std::map<std::string, sf::Texture>& textures)
    : Gun(x, y, textures) {
  bullet_ = std::make_unique<RifleBullet>(x, y, textures);
  SetTexture("rifle");
}

char Rifle::GunType() { return 'A'; }

RocketLauncher::RocketLauncher(float x, float y,
                               std::map<std::string, sf::Texture>& textures)
    : Gun(x, y, textures) {
  bullet_ = std::make_unique<Rocket>(x, y, textures);
  SetTexture("rocket_launcher");
}

char RocketLauncher::GunType() { return 'R'; }