#include "box.hpp"

Box::Box(float x, float y, sf::Texture& texture, float mass, int hp)
    : Rigid(x, y, texture, mass, hp) {}

Concrete::Concrete(float x, float y,
                   std::map<std::string, sf::Texture> textures)
    : Box(x, y, textures.at("concrete"), 100, 1000) {
  damaged_ = std::make_optional(textures.at("concrete_damaged"));
  points_ = 100;
}

Wood::Wood(float x, float y, std::map<std::string, sf::Texture> textures)
    : Box(x, y, textures.at("wood"), 50, 500) {
  damaged_ = std::make_optional(textures.at("wood_damaged"));
  points_ = 70;
}

Glass::Glass(float x, float y, std::map<std::string, sf::Texture> textures)
    : Box(x, y, textures.at("glass"), 40, 300) {
  damaged_ = std::make_optional(textures.at("glass_damaged"));
  points_ = 50;
}