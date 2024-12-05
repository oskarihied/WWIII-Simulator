#ifndef BOX_HPP
#define BOX_HPP

#include "rigid.hpp"

class Box : public Rigid {
 public:
  Box(float x, float y, sf::Texture& texture, float mass, int hp);
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