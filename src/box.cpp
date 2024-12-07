#include "box.hpp"

Box::Box(float x, float y, std::map<std::string, sf::Texture>& textures)
    : Physical(x, y, textures) {
  SetType(EntityType::BOX);
}

Concrete::Concrete(float x, float y,
                   std::map<std::string, sf::Texture>& textures)
    : Box(x, y, textures) {
  maxHealth_ = 1000;
  health_ = 1000;
  mass_ = 100;
  points_ = 100;
  SetTexture("concrete");
}

void Concrete::BecomeDamaged() {
  if (health_ < maxHealth_ * 0.9f) {
    SetTexture("concrete_damaged");
  }
}

Wood::Wood(float x, float y, std::map<std::string, sf::Texture>& textures)
    : Box(x, y, textures) {
  maxHealth_ = 500;
  health_ = 500;
  mass_ = 50;
  points_ = 70;
  SetTexture("wood");
}

void Wood::BecomeDamaged() {
  if (health_ < maxHealth_ * 0.9f) {
    SetTexture("wood_damaged");
  }
}

Glass::Glass(float x, float y, std::map<std::string, sf::Texture>& textures)
    : Box(x, y, textures) {
  maxHealth_ = 300;
  health_ = 300;
  mass_ = 40;
  points_ = 50;
  SetTexture("glass");
}

void Glass::BecomeDamaged() {
  if (health_ < maxHealth_ * 0.9f) {
    SetTexture("glass_damaged");
  }
}