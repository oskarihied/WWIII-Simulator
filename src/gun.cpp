#include "gun.hpp"

Gun::Gun(float x, float y, sf::Texture& texture, Bullet* bullet) 
    : Entity(x, y, texture), bullet_(bullet) {}
       
Bullet* Gun::GetBullet() {
    return bullet_;
}