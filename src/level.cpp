#include "level.hpp"

Level::Level(sf::Texture& background, bool isMenu)
    : camera_(new Camera(-1, 4)),
      physics_(new Physics()),
      entities_(physics_->GetEntities()),
      isMenu_(isMenu) {
  background_.setTexture(background);
  background_.setScale(2.0f, 2.0f);
}

Camera* Level::GetCam() { return camera_; }

bool Level::IsMenu() { return isMenu_; }

void Level::AddEntity(Entity* entity) {
  // entities_.push_back(entity);
}

void Level::AddBox(Box* box) {
  physics_->AddBox(box);
  // entities_.push_back(box);
}

void Level::AddGround(Ground* ground) { physics_->AddGround(ground); }

void Level::AddExplosion(Explosion* explosion, float force) {
  nonPhysicals_.push_back((Entity*)explosion);
  explosions_.push_back(explosion);
  Pos pos = explosion->GetPos();
  physics_->SpawnExplosion(pos, force);
}

std::vector<Explosion*> Level::GetExplosions() { return explosions_; }

void Level::AddEnemy(Enemy* enemy) { physics_->AddEnemy(enemy); }

void Level::AddBoxes(std::vector<Box*> boxes) {
  for (auto it : boxes) {
    physics_->AddBox(it);
  }
}

void Level::AddButton(Button* button) {
  buttons_.push_back(button);
  nonPhysicals_.push_back(button->GetEntity());
}

sf::Sprite& Level::GetBackground() { return background_; }

Physics* Level::GetPhysics() { return physics_; }

void Level::Fire(float speed) {
  if (currentGun_) {
    Bullet* b = currentGun_->GetBullet();

    Pos location = CurrentGun()->GetPos();
    float angle = -CurrentGun()->GetRotation() * (M_PI / 180);
    float x = cos(angle);
    float y = sin(angle);

    b->MoveTo(location.GetX() + x, location.GetY() + y);
    b->UpdateVel(x * speed * 30, y * speed * 30);
    b->RotationTo(-CurrentGun()->GetRotation());

    physics_->AddBullet(b);

    guns_.pop_back();
    if (guns_.empty()) {
      currentGun_ = nullptr;
    } else {
      currentGun_ = guns_.back();
    }
  }
}

void Level::AddNonPhysicalEntity(Entity* entity) {
  nonPhysicals_.push_back(entity);
}

std::vector<Entity*> Level::GetEntities() { return entities_; }

std::vector<std::pair<std::string, int>> Level::GetLeaderboard() {
  return leaderboard_;
}

void Level::AddScore(std::string name, int score) {
  leaderboard_.push_back(std::make_pair(name, score));
}

void Level::AddScores(std::vector<std::pair<std::string, int>> scores) {
  for (auto it : scores) {
    leaderboard_.push_back(it);
  }
}

std::vector<Entity*> Level::GetNonPhysicalEntities() { return nonPhysicals_; }

void Level::RemovePhysicalEntity(Entity* entity) {
  physics_->RemovePhysicalEntity(entity);
}

void Level::RemoveNonPhysicalEntity(Entity* entity) {
  int index = -1;
  int i = 0;
  for (Entity* ent : nonPhysicals_) {
    if (ent == entity) {
      index = i;
    }
    i++;
  }

  if (index != -1) {
    nonPhysicals_.erase(nonPhysicals_.begin() + index);
  }
}

void Level::RemoveExplosion(Explosion* entity) {
  int index = -1;
  int i = 0;
  for (Explosion* ent : explosions_) {
    if (ent == entity) {
      index = i;
    }
    i++;
  }

  if (index != -1) {
    explosions_.erase(explosions_.begin() + index);
    RemoveNonPhysicalEntity(entity);
  }
}

std::vector<Button*> Level::GetButtons() { return buttons_; }

Entity* Level::CurrentGun() { return currentGun_; }

void Level::AddGun(Gun* gun) {
  guns_.push_back(gun);
  currentGun_ = gun;
}