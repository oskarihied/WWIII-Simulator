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

void Level::AddBoxes(std::vector<Box*> boxes) {
    for(auto it : boxes){
        physics_->AddBox(it);
    }
}

Physics* Level::GetPhysics() {
    return physics_;
}

void Level::AddPhysicalEntity(Entity* entity) {
    //physics_.AddBox(entity);
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