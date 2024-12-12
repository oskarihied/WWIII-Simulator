#ifndef BOX_HPP
#define BOX_HPP

#include "physical.hpp"

class Box : public Physical {
 public:
  Box(float x, float y);

  const bool IsDynamic() override;
};

class Concrete : public Box {
 public:
  Concrete(float x, float y);

  void BecomeDamaged() override;
};

class Wood : public Box {
 public:
  Wood(float x, float y);

  void BecomeDamaged() override;
};

class Glass : public Box {
 public:
  Glass(float x, float y);

  void BecomeDamaged() override;
};

#endif