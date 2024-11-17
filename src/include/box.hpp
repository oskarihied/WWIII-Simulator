#ifndef BOX_HPP
#define BOX_HPP

#include "rigid.hpp"

class Box : public Rigid {
 public:
  Box(float x, float y);
  Box(float x, float y, std::string image, float mass, int hp, int dur);
  Box(float x, float y, sf::Texture& texture, float mass, int hp, int dur);

 protected:
  int durability_;
  std::vector<Rigid> contains_;
};

#endif