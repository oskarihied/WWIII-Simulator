#include "physics.hpp"

#include <box2d/base.h>

#include <iostream>

Physics::Physics() {
  b2WorldDef worldDef = b2DefaultWorldDef();
  worldDef.gravity = (b2Vec2){0.0f, -9.81f};
  simulationWorld_ = b2CreateWorld(&worldDef);
}

void Physics::SimulateWorld(float simulationStep) {
  // Update simulation Objects locations
  b2World_Step(simulationWorld_, simulationStep, 4);

  // Verify that all entities match simulation bodies
  if (b2bodies_.size() != entities_.size()) {
    throw std::invalid_argument(
        "Vectors entities and b2bodies must be the same size.");
  }

  // Update entity location from simulation bodies locations
  for (uint i = 0; i < entities_.size(); i++) {
    b2Vec2 pos = b2Body_GetPosition(b2bodies_[i]);
    entities_[i]->MoveTo(Pos(pos.x, pos.y));
    // std::cout << "x: " << pos.x << " y: " << pos.y << std::endl;
  }
};

b2BodyId Physics::AddBox(Box* box) {
  b2BodyDef bodyDef = b2DefaultBodyDef();
  bodyDef.type = b2_dynamicBody;
  bodyDef.position = (b2Vec2){box->GetPos().GetX(), box->GetPos().GetY()};
  b2BodyId bodyId = b2CreateBody(simulationWorld_, &bodyDef);

  b2Polygon dynamicBox =
      b2MakeBox(box->GetWidth() / 2.0, box->GetHeight() / 2.0);

  b2ShapeDef shapeDef = b2DefaultShapeDef();
  shapeDef.density = 1.0f;
  shapeDef.friction = 0.3f;

  b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);

  b2bodies_.push_back(bodyId);
  entities_.push_back(box);

  return bodyId;
};

b2BodyId Physics::AddGround(Ground* ground) {
  b2BodyDef groundBodyDef = b2DefaultBodyDef();
  groundBodyDef.position = (b2Vec2){0.0f, -10.0f};
  b2BodyId groundId = b2CreateBody(simulationWorld_, &groundBodyDef);

  b2Polygon groundBox = b2MakeBox(50.0f, 10.0f);

  b2ShapeDef groundShapeDef = b2DefaultShapeDef();
  b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

  b2bodies_.push_back(groundId);
  entities_.push_back(ground);

  return groundId;
};

void Physics::SetVelocity(b2BodyId* body, float xVel, float yVel) {
  b2Body_SetLinearVelocity(*body, (b2Vec2){xVel, yVel});
};

void Physics::SetPosition(b2BodyId* body, float xPos, float yPos,
                          b2Rot rotation) {
  b2Body_SetTransform(*body, (b2Vec2){xPos, yPos}, rotation);
};
