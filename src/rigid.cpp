#include "rigid.hpp"

// Rigid::Rigid(float x, float y) : Physical(x, y), maxHP_(1), currentHP_(1) {}

Rigid::Rigid(float x, float y, std::string image, float mass, int hp)
    : Physical(x, y, image, mass, 1.0f, 1.0f), maxHP_(hp), currentHP_(hp) {}

Rigid::Rigid(float x, float y, sf::Texture& texture, float mass, int hp)
    : Physical(x, y, texture, mass, 1.0f, 1.0f), maxHP_(hp), currentHP_(hp) {
        maxHealth = maxHP_;
        health_ = currentHP_;
        mass = mass_;
    }

Rigid::Rigid(float x, float y, float xVel, float yVel, std::string image,
             float w, float h, float mass, int hp)
    : Physical(x, y, xVel, yVel, image, mass, w, h),
      maxHP_(hp),
      currentHP_(hp) {}

Rigid::Rigid(float x, float y, float xVel, float yVel, sf::Texture& texture, float w,
        float h,  float mass, int hp)
    : Physical(x, y, xVel, yVel, texture, mass, w, h), maxHP_(hp), currentHP_(hp) {
        maxHealth = maxHP_;
        health_ = currentHP_;
        mass = mass_;
    }