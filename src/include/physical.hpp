#ifndef PHYSICAL_HPP
#define PHYSICAL_HPP

#include "entity.hpp"

//Entity that has physical properties
//Has a physics body
class Physical : public Entity {
 public:
  Physical(float x, float y);

  //virtual destructor
  virtual ~Physical() = 0;

  //returns: entitys mass
  const float& GetMass();

  //returns whether the entity can move or not
  virtual const bool IsDynamic() = 0;

 protected:
  //mass
  float mass_;
};

#endif