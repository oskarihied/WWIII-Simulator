#include "physics.hpp"

#include <iostream>

constexpr float EXPLOSION_DAMAGE = 3.0f;
constexpr float ENTITY_DAMAGE = 0.2f;
constexpr float BULLET_DAMAGE= 10.0f;
constexpr bool PRINT_DEBUG = true;

Physics::Physics(std::vector<std::unique_ptr<Physical>>& entities)
    : entities_(entities) {
  b2WorldDef worldDef = b2DefaultWorldDef();
  worldDef.gravity = (b2Vec2){0.0f, -9.81f};
  worldDef.hitEventThreshold = 0.5f;
  simulationWorld_ = b2CreateWorld(&worldDef);
}

Physics::~Physics() {
  b2DestroyWorld(simulationWorld_);
}

void Physics::SimulateWorld(float simulationStep) {
  // Update simulation Objects locations
  b2World_Step(simulationWorld_, simulationStep, 4);

  // Calculate ground and collision damage
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
    float entityDamage = damageMultiplier * ENTITY_DAMAGE;
    bool is1Ground = entities_[inx1]->GetType() == Entity::EntityType::GROUND;
    bool is2Ground = entities_[inx2]->GetType() == Entity::EntityType::GROUND;

    float mass1, mass2;
    if (is1Ground)
      mass1 = 500;
    else
      mass1 = b2Body_GetMass(bid1);
    if (is2Ground)
      mass2 = 500;
    else
      mass2 = b2Body_GetMass(bid2);

    bool s1 = entities_[inx1]->GetType() == Entity::EntityType::BULLET;
    bool s2 = entities_[inx2]->GetType() == Entity::EntityType::BULLET;

    if (!s1 && !s2) {
      entities_[inx1]->ChangeHealth(entityDamage * mass2);
      entities_[inx2]->ChangeHealth(entityDamage * mass1);
    } else if (s1) {
      entities_[inx1]->ChangeHealth(entityDamage * mass2);
      entities_[inx2]->ChangeHealth(entityDamage * mass1 * BULLET_DAMAGE);
    } else {
      entities_[inx1]->ChangeHealth(entityDamage * mass2 * BULLET_DAMAGE);
      entities_[inx2]->ChangeHealth(entityDamage * mass1);
    }
    if (PRINT_DEBUG) {
      std::cout << s1;
      std::cout << s2 << std::endl;
      std::cout << "ent1: " << entities_[inx1]->GetHealth() << std::endl;
      std::cout << "ent2: " << entities_[inx2]->GetHealth() << std::endl;
      std::cout << events.hitEvents[j].approachSpeed << std::endl;
    }
  }

  // Verify that all entities match simulation bodies
  if (b2bodies_.size() != entities_.size()) {
    throw std::invalid_argument(
        "Vectors entities and b2bodies must be the same size.");
  }

  // Update ground location from simulation bodies locations
  for (uint i = 0; i < entities_.size(); i++) {
    b2BodyId body = b2bodies_[i];
    b2Vec2 pos = b2Body_GetPosition(body);
    b2Vec2 vel = b2Body_GetLinearVelocity(body);

    auto& ent = entities_[i];
    ent->UpdateVel(vel.x, vel.y);
    ent->MoveTo(pos.x, pos.y);
    ent->RotationTo(acos(b2Body_GetRotation(body).c) * (180 / M_PI));
  }
};

void Physics::SpawnExplosion(Vector pos, float force) {
  int i = 0;
  for (auto& ground : entities_) {
    if (ground->GetType() == Entity::EntityType::BULLET ||
        ground->GetType() == Entity::EntityType::GROUND ||
        ground->GetType() == Entity::EntityType::UNDEFINED)
      continue;
    Vector& entPos = ground->GetPos();
    Vector vector = Vector(entPos);
    float distance = std::max(pos.Distance(entPos), 0.1f);

    b2Vec2 forceVec = b2Vec2{force * vector.GetX() / (float)pow(distance, 2),
                             force * vector.GetY() / (float)pow(distance, 2)};
    b2Vec2 position = b2Vec2{pos.GetX(), pos.GetY()};

    b2Body_ApplyForce(b2bodies_[i], forceVec, position, true);
    ground->ChangeHealth(-(force * EXPLOSION_DAMAGE) / distance);

    i++;
  }
}

void Physics::RemovePhysicalEntity(std::unique_ptr<Physical>& entity) {
  int index = -1;

  size_t i;
  for (i = 0; i < entities_.size(); i++) {
    if (entities_[i].get() == entity.get()) {
      index = i;
      break;
    }
  }

  b2Body_Disable(b2bodies_[index]);
  entities_[i]->Die();
}
