#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <box2cpp/box2cpp.h>

#include "box.hpp"
#include "bullet.hpp"
#include "enemy.hpp"
#include "ground.hpp"

//Simulates physics of the game
class Physics {
 public:
  //params: list of entities that are in the scene
  Physics(std::vector<std::unique_ptr<Physical>>& entities);

  //destructor
  ~Physics();

  //Progresses the world by an amount. Calculates new positions, collisions, damages and more
  //params: amount of time from last step
  void SimulateWorld(float simulationStep);

  //Adds a new box to the scene
  //params: the entity that the box corresponds to
  template <typename T>
  void AddBoxBody(std::unique_ptr<T>& body) {
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.position = (b2Vec2){body->GetPos().GetX(), body->GetPos().GetY()};

    //creating the physics body based on entity dimensions
    b2Polygon bodyBox =
        b2MakeBox(body->GetWidth() / 2.0f, body->GetHeight() / 2.0f);
    b2ShapeDef bodyShapeDef = b2DefaultShapeDef();

    //enabling physics if the body is dynamic
    if (body->IsDynamic()) {
      bodyDef.type = b2_dynamicBody;
      bodyDef.linearVelocity =
          (b2Vec2){body->GetVel().GetX(), body->GetVel().GetY()};
      //setting right rotation
      const float& bodyRot = body->GetRotation() * (M_PI / 180);
      bodyDef.rotation = (b2Rot){cos(bodyRot), sin(bodyRot)};

      //Setting right mass
      bodyShapeDef.density = body->GetMass();
      bodyShapeDef.friction = 0.3f;
      bodyShapeDef.enableHitEvents = true;
    }

    //creating and adding to list
    b2BodyId bodyId = b2CreateBody(simulationWorld_, &bodyDef);
    b2CreatePolygonShape(bodyId, &bodyShapeDef, &bodyBox);
    b2bodies_.push_back(bodyId);
  }

  //Spawns new explosion to the physics
  //params: position of the explosion, force
  void SpawnExplosion(Vector& pos, float force);

  //Removes an entity
  //params: enity to be removed
  void RemovePhysicalEntity(std::unique_ptr<Physical>& entity);

 private:
  //the simulation world id
  b2WorldId simulationWorld_;

  //list of the entities
  std::vector<std::unique_ptr<Physical>>& entities_;
  //list of the bodies corresponding to entities
  std::vector<b2BodyId> b2bodies_;
};

#endif