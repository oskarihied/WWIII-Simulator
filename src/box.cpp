#include "box.hpp"

Box::Box(float x, float y)
    : Rigid(x, y), durability_(1) {}

Box::Box(float x, float y, std::string image, float mass, int hp, int dur)
    : Rigid(x, y, image, mass, hp), durability_(dur) {}

Box::Box(float x, float y, sf::Texture& texture, float mass, int hp, int dur)
    : Rigid(x, y, texture, mass, hp), durability_(dur) {}