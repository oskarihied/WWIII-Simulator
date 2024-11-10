#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <box2d/box2d.h>

#include "box.hpp"
#include "bullet.hpp"
#include "ground.hpp"

class Physics {
 public:
  Physics();

  // simulate the simulation one simulation step
  void SimulateWorld(float simulationStep);

  b2BodyId AddBox(Box* box);
  b2BodyId AddGround(Ground* ground);
  b2BodyId AddBullet(Bullet* bullet);

  void SetVelocity(b2BodyId body, float xVel, float yVel);
  void SetPosition(b2BodyId body, float xPos, float yPos, b2Rot rotation);

  const std::vector<Entity*>& GetEntities() const { return entities_; }
  const std::vector<b2BodyId>& GetBodies() const { return b2bodies_; }

 private:
  b2WorldId simulationWorld_;
  std::vector<Entity*> entities_;
  std::vector<b2BodyId> b2bodies_;
};

#endif