#include "level.hpp"

#include <exception>

Level::Level(sf::Texture& background,
             std::map<std::string, sf::SoundBuffer>& sfx, bool isMenu)
    : camera_(new Camera(-1, 4)),
      physics_(new Physics()),
      sfx_(sfx),
      entities_(physics_->GetEntities()),
      isMenu_(isMenu) {
  background_.setTexture(background);
  background_.setScale(1.0f, 1.0f);
}

Level::~Level() {
  delete camera_;
  delete physics_;
}

Camera* Level::GetCam() { return camera_; }

bool Level::IsMenu() { return isMenu_; }

void Level::AddBox(Box* box) { physics_->AddBox(box); }

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
    switch (currentGun_->GetType()) {
      case 'A':
        PlaySound("rifle");
        break;

      case 'R':
        PlaySound("launcher");
        break;

      default:
        throw std::exception();
    }

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

    timer_ = 0;
    bulletTimer_ = true;
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

Gun* Level::CurrentGun() { return currentGun_; }

void Level::AddGun(Gun* gun) {
  guns_.push_back(gun);
  currentGun_ = gun;
}

void Level::AddBulletTimer(float time) {
  if (bulletTimer_) {
    timer_ += time;
  }
}

float Level::GetTimer() {
  if (bulletTimer_) {
    return timer_;
  } else {
    return 0;
  }
}

void Level::SetTimer(bool timer) {
  timer_ = 0;
  bulletTimer_ = timer;
}

void Level::AddPoints(int points) { points_ += points; }

int Level::GetPoints() { return points_; }

void Level::PlaySound(const std::string name) {
  sf::Sound* sound = new sf::Sound(sfx_.at(name));
  sound->play();
  onGoingSounds_.push_back(sound);
}

std::vector<sf::Sound*>& Level::GetSounds() { return onGoingSounds_; }

std::vector<Gun*> Level::GetGuns() {return guns_;}