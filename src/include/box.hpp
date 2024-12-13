#ifndef BOX_HPP
#define BOX_HPP

#include "physical.hpp"


//Basic structure in the level
class Box : public Physical {
 public:
  //params: Box's x and y coordinates
  Box(float x, float y);

  //Boxes are dynamic
  //returns true
  const bool IsDynamic() override;
};

//Concrete Box
class Concrete : public Box {
 public:
  Concrete(float x, float y);

  //For changing the right texture when damaged
  void BecomeDamaged() override;
};

//Wood Box
class Wood : public Box {
 public:
  Wood(float x, float y);

  //For changing the right texture when damaged
  void BecomeDamaged() override;
};

//Glass Box
class Glass : public Box {
 public:
  Glass(float x, float y);

  //For changing the right texture when damaged
  void BecomeDamaged() override;
};

#endif