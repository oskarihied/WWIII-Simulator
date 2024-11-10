#include "level.hpp"

Level::Level()
    : camera_(new Camera(0, 5)),
      physics_(new Physics()),
      entities_(physics_->GetEntities()) {
  bullets_.push_back(new RegularBullet(-3, -2, 0, 0));
  // entities_ = physics_->GetEntities();
}

Camera* Level::GetCam() { return camera_; }

void Level::AddEntity(Entity* entity) {
  // entities_.push_back(entity);
}

void Level::AddBox(Box* box) {
  physics_->AddBox(box);
  // entities_.push_back(box);
}

void Level::Fire() {
  if (!bullets_.empty()) {
    Bullet* b = bullets_.back();
    bullets_.pop_back();
    b->UpdateVel(30, 30);
    physics_->AddBullet(b);
  }
}

Physics* Level::GetPhysics() { return physics_; }

void Level::AddPhysicalEntity(Entity* entity) {
  // physics_.AddBox(entity);
}

std::vector<Entity*> Level::GetEntities() { return entities_; }