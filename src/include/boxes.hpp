#include "box.hpp"
#include "game.hpp"

class Concrete : public Box {
 public:
  Concrete(float x, float y, std::map<std::string, sf::Texture> textures) : Box(x, y, textures.at("concrete"), 100, 10) {
    damaged_ = std::make_optional(textures.at("concrete_damaged"));
  }
};

class Wood : public Box {
 public:
  Wood(float x, float y, std::map<std::string, sf::Texture> textures) : Box(x, y, textures.at("wood"), 50, 3) {
    damaged_ = std::make_optional(textures.at("wood_damaged"));
  }
};

class Glass : public Box {
 public:
  Glass(float x, float y, std::map<std::string, sf::Texture> textures) : Box(x, y, textures.at("glass"), 40, 3) {
    damaged_ = std::make_optional(textures.at("glass_damaged"));
  }
};