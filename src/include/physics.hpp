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

  void SimulateWorld(float simulationStep);

  void AddGround(std::unique_ptr<Ground>& ground);
  void AddBox(std::unique_ptr<Box>& box);
  void AddEnemy(std::unique_ptr<Enemy>& enemy);
  void AddBullet(std::unique_ptr<Bullet>& bullet);

  void SpawnExplosion(Vector pos, float force);

  void RemovePhysicalEntity(std::unique_ptr<Physical>& entity);

 private:
  b2WorldId simulationWorld_;

  std::vector<std::unique_ptr<Physical>>& entities_;
  std::vector<b2BodyId> b2bodies_;
};

#endif