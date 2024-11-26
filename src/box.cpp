#include "box.hpp"

Box::Box(float x, float y, sf::Texture& texture, float mass, int hp)
    : Rigid(x, y, texture, mass, hp) {}