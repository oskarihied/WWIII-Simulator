#include "level.hpp"

Level::Level()
    : camera_(new Camera(-1, 4)),
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

void Level::AddBoxes(std::vector<Box*> boxes) {
    for(auto it : boxes){
        physics_->AddBox(it);
    }
}

Physics* Level::GetPhysics() {
    return physics_;
}

void Level::Fire() {
  if (!bullets_.empty()) {
    Bullet* b = bullets_.back();
    bullets_.pop_back();
    b->UpdateVel(20, 10);
    physics_->AddBullet(b);
  }
}

void Level::AddNonPhysicalEntity(Entity* entity) {
    nonPhysicals_.push_back(entity);
}

std::vector<Entity*> Level::GetEntities() {
    return entities_;
}

std::vector<std::pair<std::string,int>> Level::GetLeaderboard() {
    return leaderboard_;
}

void Level::AddScore(std::string name, int score) {
    leaderboard_.push_back(std::make_pair(name,score));
}

void Level::AddScores(std::vector<std::pair<std::string,int>> scores) {
    for(auto it : scores) {
        leaderboard_.push_back(it);
    }
}

std::vector<Entity*> Level::GetNonPhysicalEntities(){
    return nonPhysicals_;
}

Entity* Level::CurrentGun() {
    return nonPhysicals_[guns_[0]];
}
/*
std::vector<Entity*> Level::GetGuns() {
    return guns_;
}
*/

void Level::AddGun(Entity* gun) {
    guns_.push_back(nonPhysicals_.size());
    nonPhysicals_.push_back(gun);
}