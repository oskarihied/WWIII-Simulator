#include "box.hpp"

Box::Box(float x, float y, sf::Texture& texture) : Physical(x, y, texture) {}

Concrete::Concrete(float x, float y,
                   std::map<std::string, sf::Texture> textures)
    : Box(x, y, textures.at("concrete")) {
  maxHealth_ = 1000;
  health_ = 1000;
  mass_ = 100;
  damagedTexture_ = std::make_optional(textures.at("concrete_damaged"));
  points_ = 100;
}

Wood::Wood(float x, float y, std::map<std::string, sf::Texture> textures)
    : Box(x, y, textures.at("wood")) {
  maxHealth_ = 500;
  health_ = 500;
  mass_ = 50;
  damagedTexture_ = std::make_optional(textures.at("wood_damaged"));
  points_ = 70;
}

Glass::Glass(float x, float y, std::map<std::string, sf::Texture> textures)
    : Box(x, y, textures.at("glass")) {
  maxHealth_ = 300;
  health_ = 300;
  mass_ = 40;
  damagedTexture_ = std::make_optional(textures.at("glass_damaged"));
  points_ = 50;
}