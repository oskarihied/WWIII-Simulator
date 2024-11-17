#include "box.hpp"
#include "game.hpp"

class Concrete : public Box {
 public:
  Concrete(float x, float y) : Box(x, y, "images/concrete.png", 100, 10, 10) {}
  Concrete(float x, float y, Game game) : Box(x, y, game.GetTexture("concrete"), 100, 10, 10) {}
};

class Wood : public Box {
 public:
  Wood(float x, float y) : Box(x, y, "images/wood.png", 50, 5, 3) {}
  Wood(float x, float y, Game game) : Box(x, y, game.GetTexture("wood"), 50, 5, 3) {}
};

class Glass : public Box {
 public:
  Glass(float x, float y) : Box(x, y, "images/glass.png", 40, 3, 1) {}
  Glass(float x, float y, Game game) : Box(x, y, game.GetTexture("glass"), 40, 3, 1) {}
};