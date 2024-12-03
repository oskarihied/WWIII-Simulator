#include "box.hpp"
//#include "game.hpp"

class Concrete : public Box {
 public:
  Concrete(float x, float y, sf::Texture texture) : Box(x, y, texture, 100, 10) {}
};

class Wood : public Box {
 public:
  Wood(float x, float y, sf::Texture texture) : Box(x, y, texture, 50, 3) {}
};

class Glass : public Box {
 public:
  Glass(float x, float y, sf::Texture texture) : Box(x, y, texture, 40, 3) {}
};