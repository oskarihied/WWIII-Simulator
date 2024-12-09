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

  void SimulateWorld(float simulationStep);

  template <typename T>
  void AddBoxBody(std::unique_ptr<T>& body, const bool isDynamic) {
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.position = (b2Vec2){body->GetPos().GetX(), body->GetPos().GetY()};

    b2Polygon bodyBox = b2MakeBox(body->GetWidth() / 2.0f, body->GetHeight() / 2.0f);

    b2ShapeDef bodyShapeDef = b2DefaultShapeDef();

    if (isDynamic) {
      bodyDef.type = b2_dynamicBody;
      bodyDef.linearVelocity = (b2Vec2){body->GetVel().GetX(), body->GetVel().GetY()};
      
      const float& bodyRot = body->GetRotation() * (M_PI / 180);
      bodyDef.rotation = (b2Rot){cos(bodyRot), sin(bodyRot)};

      bodyShapeDef.density = body->GetMass();
      bodyShapeDef.friction = 0.3f;
      bodyShapeDef.enableHitEvents = true;
    }

    b2BodyId bodyId = b2CreateBody(simulationWorld_, &bodyDef);

    b2CreatePolygonShape(bodyId, &bodyShapeDef, &bodyBox);

    b2bodies_.push_back(bodyId);

  }

  void SpawnExplosion(Vector pos, float force);

  void RemovePhysicalEntity(std::unique_ptr<Physical>& entity);

 private:
  b2WorldId simulationWorld_;

  std::vector<std::unique_ptr<Physical>>& entities_;
  std::vector<b2BodyId> b2bodies_;
};

#endif