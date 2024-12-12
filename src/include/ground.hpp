#ifndef GROUND_HPP
#define GROUND_HPP

#include "physical.hpp"

class Ground : public Physical {
 public:
  Ground(float x, float y);

  const bool IsDynamic() override;
};

class GroundBox : public Physical {
 public:
  GroundBox(float x, float y);

  const bool IsDynamic() override;
};

#endif