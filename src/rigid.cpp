#include "rigid.hpp"

Rigid::Rigid(float x, float y, sf::Texture& texture, float mass, int hp)
    : Physical(x, y, texture, mass, 1.0f, 1.0f), maxHP_(hp), currentHP_(hp) {
  maxHealth = maxHP_;
  health_ = currentHP_;
  mass = mass_;
}