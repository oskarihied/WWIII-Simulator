#ifndef GROUND_HPP
#define GROUND_HPP

#include "physical.hpp"

//Big ground (2 x 10 size)
class Ground : public Physical {
 public:
  Ground(float x, float y);

  //returns: false
  const bool IsDynamic() override;
};

//Small ground (1 x 1 size)
class GroundBox : public Physical {
 public:
  GroundBox(float x, float y);

  //returns: false
  const bool IsDynamic() override;
};

#endif