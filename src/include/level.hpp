#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>

#include "bullets.hpp"
#include "camera.hpp"
#include "entity.hpp"
#include "physics.hpp"

class Level {
 public:
  Level();

  Camera* GetCam();

  void AddEntity(Entity* entity);
  void AddPhysicalEntity(Entity* entity);
  void AddBox(Box* box);
  void Fire();

  Physics* GetPhysics();

  std::vector<Entity*> GetEntities();

 private:
  Camera* camera_;
  Physics* physics_;
  std::vector<Bullet*> bullets_;
  const std::vector<Entity*>& entities_;
};

#endif
