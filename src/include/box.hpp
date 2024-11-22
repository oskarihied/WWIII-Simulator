#ifndef BOX_HPP
#define BOX_HPP

#include "rigid.hpp"

class Box : public Rigid {
 public:
  Box(float x, float y, sf::Texture& texture, float mass, int hp);
};

#endif