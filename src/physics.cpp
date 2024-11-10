#include "physics.hpp"

#include <box2d/base.h>
#include <box2d/collision.h>

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
    b2BodyId body = b2bodies_[i];
    b2Vec2 pos = b2Body_GetPosition(body);
    b2Vec2 vel = b2Body_GetLinearVelocity(body);

    Entity* ent = entities_[i];
    ent->UpdateVel(vel.x, vel.y);
    ent->MoveTo(Pos(pos.x, pos.y));
    ent->RotationTo(acos(b2Body_GetRotation(body).c) * (180 / M_PI));
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
  groundBodyDef.position = (b2Vec2){0.0f, -10.5f};
  b2BodyId groundId = b2CreateBody(simulationWorld_, &groundBodyDef);

  b2Polygon groundBox = b2MakeBox(50.0f, 10.0f);

  b2ShapeDef groundShapeDef = b2DefaultShapeDef();
  b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

  b2bodies_.push_back(groundId);
  entities_.push_back(ground);

  return groundId;
};

b2BodyId Physics::AddBullet(Bullet* bullet) {
  float bx = bullet->GetPos().GetX();
  float by = bullet->GetPos().GetX();

  b2BodyDef bulletBodyDef = b2DefaultBodyDef();
  bulletBodyDef.type = b2_dynamicBody;
  bulletBodyDef.position = (b2Vec2){bx, by};
  b2BodyId bulletId = b2CreateBody(simulationWorld_, &bulletBodyDef);

  b2Capsule capsule;
  capsule.center1 = (b2Vec2){bx, by};
  capsule.center2 = (b2Vec2){bx + 1.0f, by + 1.0f};
  capsule.radius = 0.25f;

  b2ShapeDef bulletShapeDef = b2DefaultShapeDef();

  b2CreateCapsuleShape(bulletId, &bulletShapeDef, &capsule);

  SetVelocity(bulletId, bullet->GetVel().GetX(), bullet->GetVel().GetX());

  b2bodies_.push_back(bulletId);
  entities_.push_back(bullet);

  return bulletId;
};

void Physics::SetVelocity(b2BodyId body, float xVel, float yVel) {
  b2Body_SetLinearVelocity(body, (b2Vec2){xVel, yVel});
};

void Physics::SetPosition(b2BodyId body, float xPos, float yPos,
                          b2Rot rotation) {
  b2Body_SetTransform(body, (b2Vec2){xPos, yPos}, rotation);
};
