#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <box2cpp/box2cpp.h>

#include "box.hpp"
#include "bullet.hpp"
#include "enemy.hpp"
#include "ground.hpp"

class Physics {
 public:
  Physics(std::vector<std::unique_ptr<Physical>>& entities);

  ~Physics();

  // simulate the simulation one simulation step
  void SimulateWorld(float simulationStep);

  void AddBox(std::unique_ptr<Box>& box);
  void AddGround(std::unique_ptr<Ground>& ground);
  void AddBullet(std::unique_ptr<Bullet>& bullet);
  void AddEnemy(std::unique_ptr<Enemy>& enemy);

  void SetVelocity(b2BodyId body, float xVel, float yVel);
  void SetPosition(b2BodyId body, float xPos, float yPos, b2Rot rotation);

  const std::vector<b2BodyId>& GetBodies() const;

  void SpawnExplosion(Vector pos, float force);

  void RemovePhysicalEntity(std::unique_ptr<Physical>& entity);

 private:
  void Contact(b2ContactHitEvent hit);

  b2WorldId simulationWorld_;

  std::vector<std::unique_ptr<Physical>>& entities_;
  std::vector<b2BodyId> b2bodies_;
  // std::vector<int32_t> bullets_;
  // std::vector<int32_t> grounds_;
};

#endif