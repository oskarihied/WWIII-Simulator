#include "level.hpp"

Level::Level() : camera_(Camera(0, 0)) {}

Camera Level::GetCam() {
    return camera_;
}

void Level::AddEntity(Entity entity) {
    entities_.push_back(entity);
}

std::vector<Entity> Level::GetEntities() {
    return entities_;
}