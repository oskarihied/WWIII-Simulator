#include "level.hpp"

#include <exception>

#include "game.hpp"

Level::Level(Game& game) : GameView(game) {
  physics_ = std::make_unique<Physics>(physicals_);
  background_.setTexture(game_.GetTexture("background1"));
  background_.setScale(1.0f, 1.0f);
}

Level::~Level() {
  camera_ = nullptr;
  physics_ = nullptr;
}

void Level::AddBox(std::unique_ptr<Box> box) {
  physics_->AddBox(box);
  physicals_.push_back(std::move(box));
}

void Level::AddGround(std::unique_ptr<Ground> ground) {
  physics_->AddGround(ground);
  physicals_.push_back(std::move(ground));
}

void Level::AddExplosion(Explosion* explosion, float force) {
  nonPhysicals_.push_back(std::unique_ptr<Entity>((Entity*)explosion));
  explosions_.push_back(explosion);
  Vector pos = explosion->GetPos();
  physics_->SpawnExplosion(pos, force);
}

std::vector<Explosion*> Level::GetExplosions() { return explosions_; }

void Level::AddEnemy(std::unique_ptr<Enemy> enemy) {
  physics_->AddEnemy(enemy);
  physicals_.push_back(std::move(enemy));
}

void Level::Fire(float speed) {
  std::unique_ptr<Gun>& currentGun = guns_.back();
  if (currentGun) {
    switch (currentGun->GetType()) {
      case 'A':
        game_.PlaySound("rifle");
        break;

      case 'R':
        game_.PlaySound("launcher");
        break;

      default:
        throw std::exception();
    }

    auto& b = currentGun->GetBullet();

    float angle = -currentGun->GetRotation() * (M_PI / 180);
    float x = cos(angle);
    float y = sin(angle);

    b->MoveTo(b->GetPos().GetX() + x, b->GetPos().GetY() + y);
    b->UpdateVel(x * speed * 30, y * speed * 30);
    b->RotationTo(-currentGun->GetRotation());

    physics_->AddBullet(b);
    currentBullet_ = b.get();
    physicals_.push_back(std::move(b));

    guns_.pop_back();

    timer_ = 0;
    bulletTimer_ = true;
  }
}

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

void Level::RemoveNonPhysicalEntity(Entity* entity) {
  int index = -1;
  int i = 0;
  for (std::unique_ptr<Entity>& ent : nonPhysicals_) {
    if (ent.get() == entity) {
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

void Level::AddGun(std::unique_ptr<Gun> gun) {
  guns_.push_back(std::move(gun));
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

std::vector<std::unique_ptr<Gun>>& Level::GetGuns() { return guns_; }

void Level::StepInTime(sf::RenderWindow& window) {
  sf::Event event;

  sf::Vector2i mousePos = sf::Mouse::getPosition(window);

  physics_->SimulateWorld(1.0f / 60.0f);

  std::unique_ptr<Gun>& currentGun = guns_.back();

  if (GetTimer() > 0 && GetTimer() <= 2 && !currentBullet_->IsDead()) {
    camera_->MoveTo(currentBullet_->GetPos().GetX() - 5,
                    camera_->GetPos().GetY());
  }

  if (currentGun.get() != nullptr) {
    AddBulletTimer(1.0f / 60.0f);

    if (GetTimer() > 2) {
      SetTimer(false);
      Vector v;

      if (currentGun->GetPos().GetX() == 0) {
        v = Vector(currentGun->GetPos().GetX() - 5, 7);
        camera_->NewAnimation(v, 15, 2);
      } else {
        v = Vector(currentGun->GetPos().GetX() - 10, 7);
        camera_->NewAnimation(v, 15, 2);
      }
    }

    camera_->AnimationStep(1.0f / 60.0f);
    std::pair<int, int> gunPos =
        game_.ToScreenPos(currentGun->GetPos(), *camera_);

    float gunY = -(float)mousePos.y - gunPos.second;
    float gunX = (float)mousePos.x - gunPos.first;

    float gunRotation = atan(gunY / gunX);
    if (gunX < 0) {
      if (gunY < 0) {
        gunRotation = -M_PI + gunRotation;
      } else {
        gunRotation = M_PI + gunRotation;
      }
    }

    currentGun->RotationTo(-gunRotation * (180.0f / M_PI));
  }

  while (window.pollEvent(event)) {
    float camMoveSpeed = 0.5f;
    float camZoomSpeed = 0.05f;

    if (event.type == sf::Event::KeyPressed) {
      if (!camera_->GetAnimation()) {
        if (event.key.scancode == sf::Keyboard::Scan::Up) {
          camera_->ShiftBy(0.0f, camMoveSpeed);
        }
        if (event.key.scancode == sf::Keyboard::Scan::Down) {
          camera_->ShiftBy(0.0f, -camMoveSpeed);
        }
        if (event.key.scancode == sf::Keyboard::Scan::Right) {
          camera_->ShiftBy(camMoveSpeed, 0.0f);
        }
        if (event.key.scancode == sf::Keyboard::Scan::Left) {
          camera_->ShiftBy(-camMoveSpeed, 0.0f);
        }

        if (event.key.scancode == sf::Keyboard::Scan::Comma) {
          camera_->Zoom(1 - camZoomSpeed);
        }
        if (event.key.scancode == sf::Keyboard::Scan::Period) {
          camera_->Zoom(1 + camZoomSpeed);
        }
      }
    }

    if (event.type == sf::Event::KeyReleased) {
      if (event.key.scancode == sf::Keyboard::Scan::Escape) {
        game_.SetMultiplayer(false);
        game_.StartMenu();
      }
    }

    if (event.type == sf::Event::MouseButtonPressed) {
      gunTimer_.restart();
    }

    if (event.type == sf::Event::MouseButtonReleased) {
      float vel = std::min(gunTimer_.getElapsedTime().asSeconds() / 2, 1.0f);
      if (currentGun.get() != nullptr) {
        Fire(vel);
      }
    }
  }
}

void Level::Render(sf::RenderWindow& window) {
  std::unique_ptr<Gun>& currentGun = guns_.back();

  window.draw(background_);

  for (Explosion* explosion : explosions_) {
    explosion->NextSprite();
    if (explosion->GetCount() > 10) {
      RemoveExplosion(explosion);
    }
  }

  for (std::unique_ptr<Entity>& entity : nonPhysicals_) {
    RenderEntity(entity, window);
  }

  if (currentGun.get() != nullptr) {
    RenderEntity(currentGun, window);
  }

  for (auto it = physicals_.begin(); it != physicals_.end(); ++it) {
    bool deleted = false;
    std::unique_ptr<Physical>& entity = *it;

    if (entity->IsDead()) continue;

    float scale = (1300.0f / 200.0f) / camera_->GetZoom();

    entity->GetSprite().setScale(sf::Vector2(scale, scale));
    entity->GetSprite().setRotation(-entity->GetRotation());

    std::pair<int, int> pos = game_.ToScreenPos(entity->GetPos(), *camera_);

    entity->GetSprite().setPosition(pos.first, -pos.second);

    window.draw(entity->GetSprite());

    if (!entity->IsDead()) {
      entity->BecomeDamaged();

      if (entity->GetHealth() <= 0) {
        entity->Die();
        AddPoints(entity->GetPoints());

        Vector position = entity->GetPos();
        // bool explodes = entity->Explodes();
        // currentLevel->RemovePhysicalEntity(entity);

        if (entity->Explodes()) {
          AddExplosion(new Explosion(entity->GetPos().GetX() + 0.01f,
                                     entity->GetPos().GetY() + 0.01f,
                                     game_.GetTextures()),
                       500.0f);
          game_.PlaySound("explosion");
        }
        if (entity->GetType() == Entity::EntityType::BOX ||
            entity->GetType() == Entity::EntityType::ENEMY ||
            entity->GetType() == Entity::EntityType::ENEMY) {
          deleted = true;
          physics_->RemovePhysicalEntity(entity);
        }
      }
    }

    int n = 0;
    int i = 0;
    for (std::unique_ptr<Gun>& gun : guns_) {
      if (game_.IsMultiplayer() && n % 2 == 0) {
        gun->GetSprite().setScale(sf::Vector2(0.5f, 0.5f));
        gun->GetSprite().setPosition(50, 20 + i * 40);
        window.draw(gun->GetSprite());
        i++;
      }
      n++;
    }
  }
}