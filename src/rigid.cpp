# include "rigid.hpp"

Rigid::Rigid(float x, float y)
    : Physical(x, y), maxHP_(1), currentHP_(1) {};

Rigid::Rigid(float x, float y, std::string image, float mass, int hp)
    : Physical(x, y, image, mass, 1.0f, 1.0f), maxHP_(hp), currentHP_(hp) {};