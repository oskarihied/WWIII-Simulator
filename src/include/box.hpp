#ifndef BOX_HPP
#define BOX_HPP

#include "physical.hpp"

class Box : public Physical {
 public:
  Box(float x, float y, sf::Texture& texture);
};

class Concrete : public Box {
 public:
  Concrete(float x, float y, std::map<std::string, sf::Texture> textures);
};

class Wood : public Box {
 public:
  Wood(float x, float y, std::map<std::string, sf::Texture> textures);
};

class Glass : public Box {
 public:
  Glass(float x, float y, std::map<std::string, sf::Texture> textures);
};

#endif