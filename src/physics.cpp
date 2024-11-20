#include "physics.hpp"

#include <iostream>

constexpr int BULLET_DAMAGE = 10;
constexpr int ENTITY_DAMAGE = 10;
constexpr bool PRINT_DEBUG = false;


Physics::Physics() {
  b2WorldDef worldDef = b2DefaultWorldDef();
  worldDef.gravity = (b2Vec2){0.0f, -9.81f};
  // worldDef.restitutionThreshold = 0.0f;
  worldDef.hitEventThreshold = 0.1f;
  simulationWorld_ = b2CreateWorld(&worldDef);
  // b2World_SetHitEventThreshold(simulationWorld_, 1);
}

void Physics::SimulateWorld(float simulationStep) {
  // Update simulation Objects locations
  b2World_Step(simulationWorld_, simulationStep, 4);

  // Calculate bullet and collision damage
  b2ContactEvents events = b2World_GetContactEvents(simulationWorld_); 
  for (int j = 0; j < events.hitCount; j++) {
    b2BodyId bid1 = b2Shape_GetBody(events.hitEvents[j].shapeIdA);
    b2BodyId bid2 = b2Shape_GetBody(events.hitEvents[j].shapeIdB);
    uint16_t inx1 = bid1.index1 - 1;
    uint16_t inx2 = bid2.index1 - 1;
    if (entities_[inx1]->GetType() == Entity::EntityType::UNDEFINED || entities_[inx2]->GetType() == Entity::EntityType::UNDEFINED) {continue;}
    float damageMultiplier = -(events.hitEvents[j].approachSpeed * events.hitEvents[j].approachSpeed);
    float bulletDamage = damageMultiplier * BULLET_DAMAGE; 
    float entityDamage = damageMultiplier * ENTITY_DAMAGE; 
    bool is1Ground = entities_[inx1]->GetType() == Entity::EntityType::GROUND;
    bool is2Ground = entities_[inx2]->GetType() == Entity::EntityType::GROUND;
    bool is1Bullet = entities_[inx1]->GetType() == Entity::EntityType::BULLET;
    bool is2Bullet = entities_[inx2]->GetType() == Entity::EntityType::BULLET;

    if (is1Ground + is2Ground + is1Bullet + is2Bullet > 1) 
    {continue;}
    if (is1Ground + is2Ground == 2) 
    {printf("sdfsdf\n");}
    if (is1Bullet) {
      entities_[inx2]->ChangeHealth(bulletDamage);
      if (PRINT_DEBUG) std::cout << "ent2Bullet: " << entities_[inx2]->GetHealth() << std::endl;
    } else if (is2Bullet) {
      entities_[inx1]->ChangeHealth(bulletDamage);
      if (PRINT_DEBUG) std::cout << "ent1Bullet: " << entities_[inx1]->GetHealth() << std::endl;
    } else if (is1Ground) {
      entities_[inx2]->ChangeHealth(entityDamage);
      if (PRINT_DEBUG) std::cout << "ent2Ground: " << entities_[inx2]->GetHealth() << std::endl;
    } else if (is2Ground) {
      entities_[inx1]->ChangeHealth(entityDamage);
      if (PRINT_DEBUG) std::cout << "ent1Ground: " << entities_[inx1]->GetHealth() << std::endl;
    } else {
      entities_[inx1]->ChangeHealth(entityDamage);
      entities_[inx2]->ChangeHealth(entityDamage);
      if (PRINT_DEBUG) std::cout << "ent1: " << entities_[inx1]->GetHealth() << std::endl;
      if (PRINT_DEBUG) std::cout << "ent2: " << entities_[inx2]->GetHealth() << std::endl;
      if (PRINT_DEBUG) std::cout << events.hitEvents[j].approachSpeed << std::endl;
    }

  }

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
  box->SetType(Entity::EntityType::BOX);
  b2BodyDef bodyDef = b2DefaultBodyDef();
  bodyDef.type = b2_dynamicBody;
  bodyDef.position = (b2Vec2){box->GetPos().GetX(), box->GetPos().GetY()};
  b2BodyId bodyId = b2CreateBody(simulationWorld_, &bodyDef);

  b2Polygon dynamicBox =
      b2MakeBox(box->GetWidth() / 2.0, box->GetHeight() / 2.0);

  b2ShapeDef shapeDef = b2DefaultShapeDef();
  shapeDef.density = 1.0f;
  shapeDef.friction = 0.3f;
  shapeDef.enableHitEvents = true;
  b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);

  b2bodies_.push_back(bodyId);
  entities_.push_back(box);

  return bodyId;
};

b2BodyId Physics::AddGround(Ground* ground) {
  ground->SetType(Entity::EntityType::GROUND);
  b2BodyDef groundBodyDef = b2DefaultBodyDef();
  groundBodyDef.position =
      (b2Vec2){ground->GetPos().GetX(), ground->GetPos().GetY() - 0.5f};
  b2BodyId groundId = b2CreateBody(simulationWorld_, &groundBodyDef);

  b2Polygon groundBox = b2MakeBox(10.0f, 1.0f);

  b2ShapeDef groundShapeDef = b2DefaultShapeDef();
  b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

  b2bodies_.push_back(groundId);
  entities_.push_back(ground);
  grounds_.push_back(groundId.index1 - 1);

  return groundId;
};

b2BodyId Physics::AddBullet(Bullet* bullet) {
  bullet->SetType(Entity::EntityType::BULLET);
  float bx = bullet->GetPos().GetX();
  float by = bullet->GetPos().GetY();

  b2BodyDef bulletBodyDef = b2DefaultBodyDef();
  bulletBodyDef.type = b2_dynamicBody;
  bulletBodyDef.position = (b2Vec2){bx, by};
  b2BodyId bulletId = b2CreateBody(simulationWorld_, &bulletBodyDef);

  b2ShapeDef bulletShapeDef = b2DefaultShapeDef();
  bulletShapeDef.enableHitEvents = true;
  bulletShapeDef.density = 1;

  b2Capsule capsule;
  capsule.center1 = (b2Vec2){bx, by};
  capsule.center2 = (b2Vec2){bx + 1.0f, by + 1.0f};
  capsule.radius = 0.25f;

  b2CreateCapsuleShape(bulletId, &bulletShapeDef, &capsule);

  SetVelocity(bulletId, bullet->GetVel().GetX(), bullet->GetVel().GetY());

  b2bodies_.push_back(bulletId);
  entities_.push_back(bullet);
  bullets_.push_back(bulletId.index1);
  return bulletId;
};

void Physics::SetVelocity(b2BodyId body, float xVel, float yVel) {
  b2Body_SetLinearVelocity(body, (b2Vec2){xVel, yVel});
};

void Physics::SetPosition(b2BodyId body, float xPos, float yPos,
                          b2Rot rotation) {
  b2Body_SetTransform(body, (b2Vec2){xPos, yPos}, rotation);
};

void Physics::Contact(b2ContactHitEvent contact) {
}