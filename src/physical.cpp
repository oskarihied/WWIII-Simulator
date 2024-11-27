#include "physical.hpp"

Physical::Physical(float x, float y)
    : Entity(x, y), mass_(1), width_(1.0f), height_(1.0f) {};

Physical::Physical(float x, float y, std::string image, float mass, float width,
                   float height)
    : Entity(x, y, image), mass_(mass), width_(width), height_(height) {};

Physical::Physical(float x, float y, sf::Texture& texture, float mass, float width,
                   float height)
    : Entity(x, y, texture), mass_(mass), width_(width), height_(height) {};

Physical::Physical(float x, float y, float xVel, float yVel, std::string image,
                   float mass, float width, float height)
    : Entity(x, y, xVel, yVel, image),
      mass_(mass),
      width_(width),
      height_(height) {};

Physical::Physical(float x, float y, float xVel, float yVel, sf::Texture& texture, float mass, float width, float height) 
    : Entity(x, y, xVel, yVel, texture), mass_(mass), width_(width), height_(height) {}

float Physical::GetWidth() { return width_; };

float Physical::GetHeight() { return height_; };

float Physical::GetMass() { return mass_; };