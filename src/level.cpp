#include "level.hpp"

Level::Level() : camera_(new Camera(0, 5)), physics_(new Physics()), entities_(physics_->GetEntities())  {
    //entities_ = physics_->GetEntities();
}

Camera* Level::GetCam() {
    return camera_;
}

void Level::AddEntity(Entity* entity) {
    //entities_.push_back(entity);
}

void Level::AddBox(Box* box) {
    physics_->AddBox(box);
    //entities_.push_back(box);
}

Physics* Level::GetPhysics() {
    return physics_;
}

void Level::AddNonPhysicalEntity(Entity* entity) {
    nonPhysicals_.push_back(entity);
}

std::vector<Entity*> Level::GetEntities() {
    return entities_;
}

std::vector<Entity*> Level::GetNonPhysicalEntities(){
    return nonPhysicals_;
}