#ifndef PHYSICAL_HPP
#define PHYSICAL_HPP

#include "entity.hpp"

class Physical : public Entity {
 public:
  Physical(float x, float y);

  virtual ~Physical() = 0;

  const float& GetMass();

  virtual const bool IsDynamic() = 0;

 protected:
  float mass_;
};

#endif