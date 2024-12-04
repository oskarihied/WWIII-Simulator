#include "physics.hpp"

#include <iostream>

constexpr int BULLET_DAMAGE = 10;
constexpr float ENTITY_DAMAGE = 0.2;
constexpr bool PRINT_DEBUG = true;

Physics::Physics() {
  b2WorldDef worldDef = b2DefaultWorldDef();
  worldDef.gravity = (b2Vec2){0.0f, -9.81f};
  // worldDef.restitutionThreshold = 0.0f;
  worldDef.hitEventThreshold = 0.5f;
  simulationWorld_ = b2CreateWorld(&worldDef);
  // b2World_SetHitEventThreshold(simulationWorld_, 1);
}

Physics::~Physics() {
  for (auto it : entities_) {
    delete it;
  }
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

    if (entities_[inx1]->GetType() == Entity::EntityType::UNDEFINED ||
        entities_[inx2]->GetType() == Entity::EntityType::UNDEFINED) {
      continue;
    }

    float damageMultiplier = -(events.hitEvents[j].approachSpeed *
                               events.hitEvents[j].approachSpeed);
    float bulletDamage = damageMultiplier * BULLET_DAMAGE;
    float entityDamage = damageMultiplier * ENTITY_DAMAGE;
    bool is1Ground = entities_[inx1]->GetType() == Entity::EntityType::GROUND;
    bool is2Ground = entities_[inx2]->GetType() == Entity::EntityType::GROUND;
    bool is1Bullet = entities_[inx1]->GetType() == Entity::EntityType::BULLET;
    bool is2Bullet = entities_[inx2]->GetType() == Entity::EntityType::BULLET;

    if (is1Ground + is2Ground + is1Bullet + is2Bullet > 1) {continue;}

    // if (is1Bullet) {
    //   entities_[inx2]->ChangeHealth(bulletDamage * b2Body_GetMass(bid1));
    //   if (PRINT_DEBUG) std::cout << "ent2Bullet: " << entities_[inx2]->GetHealth() << std::endl;
    // } else if (is2Bullet) {
    //   entities_[inx1]->ChangeHealth(bulletDamage * b2Body_GetMass(bid2));
    //   if (PRINT_DEBUG) std::cout << "ent1Bullet: " << entities_[inx1]->GetHealth() << std::endl;
    //  else 
    if (is1Ground) {
      entities_[inx2]->ChangeHealth(entityDamage * 10);
      if (PRINT_DEBUG) std::cout << "ent2Ground: " << entities_[inx2]->GetHealth() << std::endl;
    } else if (is2Ground) {
      entities_[inx1]->ChangeHealth(entityDamage * 10);
      if (PRINT_DEBUG) std::cout << "ent1Ground: " << entities_[inx1]->GetHealth() << std::endl;
    } else {
      entities_[inx1]->ChangeHealth(entityDamage * b2Body_GetMass(bid2));
      entities_[inx2]->ChangeHealth(entityDamage * b2Body_GetMass(bid1));
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
  shapeDef.density = box->GetMass();
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
  // grounds_.push_back(groundId.index1 - 1);

  return groundId;
};

b2BodyId Physics::AddBullet(Bullet* bullet) {
  bullet->SetType(Entity::EntityType::BULLET);

  float pos_x = bullet->GetPos().GetX();
  float pos_y = bullet->GetPos().GetY();

  float rot = bullet->GetRotation() * (M_PI / 180);
  b2Rot bruht;
  bruht.c = cos(rot);
  bruht.s = sin(rot);

  b2BodyDef bulletBodyDef = b2DefaultBodyDef();
  bulletBodyDef.type = b2_dynamicBody;

  b2BodyId bulletId = b2CreateBody(simulationWorld_, &bulletBodyDef);

  b2ShapeDef bulletShapeDef = b2DefaultShapeDef();
  bulletShapeDef.enableHitEvents = true;
  bulletShapeDef.density = bullet->GetMass();
  bulletShapeDef.friction = 0.3f;
  bulletShapeDef.enableHitEvents = true;

  b2Polygon dynamicBox =
      b2MakeBox(bullet->GetWidth() / 2.0, bullet->GetHeight() / 2.0);

  b2CreatePolygonShape(bulletId, &bulletShapeDef, &dynamicBox);

  b2Body_SetTransform(bulletId, (b2Vec2){pos_x, pos_y}, bruht);

  SetVelocity(bulletId, bullet->GetVel().GetX(), bullet->GetVel().GetY());

  b2bodies_.push_back(bulletId);
  entities_.push_back(bullet);
  // bullets_.push_back(bulletId.index1);
  return bulletId;
};

b2BodyId Physics::AddEnemy(Enemy* enemy) {
  enemy->SetType(Entity::EntityType::ENEMY);
  enemy->SetHealth(100);
  b2BodyDef bodyDef = b2DefaultBodyDef();
  bodyDef.type = b2_dynamicBody;
  bodyDef.position = (b2Vec2){enemy->GetPos().GetX(), enemy->GetPos().GetY()};

  b2BodyId bodyId = b2CreateBody(simulationWorld_, &bodyDef);
  b2Polygon dynamicBox =
      b2MakeBox(enemy->GetWidth() / 2.0, enemy->GetHeight() / 2.0);

  b2ShapeDef shapeDef = b2DefaultShapeDef();
  shapeDef.density = 1.0f;
  shapeDef.friction = 0.3f;
  shapeDef.enableHitEvents = true;

  b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);

  b2bodies_.push_back(bodyId);
  entities_.push_back(enemy);

  return bodyId;
};

void Physics::SetVelocity(b2BodyId body, float xVel, float yVel) {
  b2Body_SetLinearVelocity(body, (b2Vec2){xVel, yVel});
};

void Physics::SetPosition(b2BodyId body, float xPos, float yPos,
                          b2Rot rotation) {
  b2Body_SetTransform(body, (b2Vec2){xPos, yPos}, rotation);
};

void Physics::Contact(b2ContactHitEvent contact) {}

void Physics::SpawnExplosion(Pos pos, float force) {
  int i = 0;
  for (Entity* entity : entities_) {
    
    if (entity->GetType() == Entity::EntityType::BULLET || entity->GetType() == Entity::EntityType::GROUND || entity->GetType() == Entity::EntityType::UNDEFINED) continue;
    Pos vector = pos.VectorTo(entity->GetPos());
    float distance = std::max(pos.Distance(entity->GetPos()), 0.1f);

    b2Vec2 forceVec = b2Vec2{force * vector.GetX() / (float)pow(distance, 2),
                             force * vector.GetY() / (float)pow(distance, 2)};
    b2Vec2 position = b2Vec2{pos.GetX(), pos.GetY()};

    b2Body_ApplyForce(b2bodies_[i], forceVec, position, true);
    entity->ChangeHealth(-(force * 10) / distance);

    i++;
  }
}

void Physics::RemovePhysicalEntity(Entity* entity) {
  int index = -1;
  
  size_t i;
  for (i = 0; i < entities_.size(); i++) {
    if (entities_[i] == entity) {
      index = i;
      break;
    }
  }
  
  b2DestroyBody(b2bodies_[index]);
  b2bodies_.erase(b2bodies_.begin() + index);
  entities_.erase(entities_.begin() + index);
  delete(entity);
  }
