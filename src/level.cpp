#include "level.hpp"

#include <exception>

#include "game.hpp"

Level::Level(Game& game) : GameView(game) {
  physics_ = std::make_unique<Physics>(physicals_);
  background_.setTexture(*FileManager::GetTexture("background1"));
  background_.setScale(1.0f, 1.0f);

  font_.loadFromFile("fonts/AmericanTypewriter.ttc");
  pointsText_.setFont(font_);
  pointsText_.setString("0");
  pointsText_.setCharacterSize(50);
  pointsText_.setPosition(200, 0);

  complete_.SetTexture("mission_complete");
  star1_.SetTexture("star_black");
  star2_.SetTexture("star_black");
  star3_.SetTexture("star_black");

  powerText_.setFont(font_);
  powerText_.setString("0");
  powerText_.setCharacterSize(50);
  powerText_.setPosition(200, 70);
}

void Level::Fire(float speed) {
  std::unique_ptr<Gun>& currentGun = guns_.back();
  if (currentGun) {
    switch (currentGun->GunType()) {
      case Gun::GunType::RIFLE:
        FileManager::PlaySound("rifle");
        break;

      case Gun::GunType::LAUNCHER:
        FileManager::PlaySound("launcher");
        break;

      default:
        throw std::exception();
    }

    auto& b = currentGun->GetBullet();

    float gunRot = currentGun->GetRotation();
    float x = cos(gunRot * (M_PI / 180));
    float y = sin(gunRot * (M_PI / 180));

    b->MoveTo(b->GetPos().GetX() + x, b->GetPos().GetY() + y);
    b->UpdateVel(x * speed * 30, y * speed * 30);
    b->RotationTo(gunRot);

    physics_->AddBoxBody(b, true);
    currentBullet_ = b.get();
    physicals_.push_back(std::move(b));

    guns_.pop_back();
    if (!guns_.empty()) {
      guns_.back()->RotationTo(gunRot);
    }

    timer_ = 0;
    bulletTimer_ = true;
  }
}

void Level::AddExplosion(Explosion* explosion, float force) {
  nonPhysicals_.push_back(std::unique_ptr<Entity>((Entity*)explosion));
  explosions_.push_back(explosion);
  Vector pos = explosion->GetPos();
  physics_->SpawnExplosion(pos, force);
}

std::vector<Explosion*> Level::GetExplosions() { return explosions_; }

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

void Level::IncrementBulletTimer(float time) {
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

void Level::AddMaxPoints(int points) { maxPoints_ += points; }

void Level::AddPoints(int points) { points_ += points; }

int Level::GetPoints() { return points_; }

std::vector<std::unique_ptr<Physical>>& Level::GetPhysicals() {
  return physicals_;
}

std::vector<std::unique_ptr<Gun>>& Level::GetGuns() { return guns_; }

const bool& Level::IsMultiplayer() { return game_.IsMultiplayer(); }

void Level::StepInTime(sf::RenderWindow& window) {
  physics_->SimulateWorld(1.0f / 60.0f);
  camera_->AnimationStep(1.0f / 60.0f);

  sf::Event event;

  sf::Vector2i mousePos = sf::Mouse::getPosition(window);

  if (GetTimer() > 0 && GetTimer() <= 2 && !currentBullet_->IsDead()) {
    camera_->MoveTo(currentBullet_->GetPos().GetX() - 5,
                    camera_->GetPos().GetY());
  }

  IncrementBulletTimer(1.0f / 60.0f);

  if (!guns_.empty()) {
    std::unique_ptr<Gun>& currentGun = guns_.back();

    if (GetTimer() > 2) {
      SetTimer(false);
      Vector v;

      if (currentGun->GetPos().GetX() == 0) {
        v = Vector(currentGun->GetPos().GetX() - 5, 12);
        camera_->NewAnimation(v, 25, 2);
      } else {
        v = Vector(currentGun->GetPos().GetX() - 10, 12);
        camera_->NewAnimation(v, 25, 2);
      }
    }

    Vector gunPos = game_.ToScreenPos(currentGun->GetPos(), *camera_);

    float gunY = -(float)mousePos.y - gunPos.GetY();
    float gunX = (float)mousePos.x - gunPos.GetX();

    float gunRotation = atan(gunY / gunX);
    if (gunX < 0) {
      if (gunY < 0) {
        gunRotation = -M_PI + gunRotation;
      } else {
        gunRotation = M_PI + gunRotation;
      }
    }

    currentGun->RotationTo(gunRotation * (180.0f / M_PI));
  }

  for (auto it = physicals_.begin(); it != physicals_.end(); ++it) {
    over_ = true;

    bool deleted = false;
    std::unique_ptr<Physical>& entity = *it;
    if (entity->GetType() == Entity::EntityType::ENEMY &&
        entity->GetHealth() > 0) {
      over_ = false;
      break;
    }
  }

  while (window.pollEvent(event)) {
    float camMoveSpeed = 0.5f;
    float camZoomSpeed = 0.05f;

    if (event.type == sf::Event::KeyPressed) {
      if (!camera_->GetAnimation()) {
        /*
        if (event.key.scancode == sf::Keyboard::Scan::Up) {
          camera_->ShiftBy(0.0f, camMoveSpeed);
        }
        if (event.key.scancode == sf::Keyboard::Scan::Down) {
          camera_->ShiftBy(0.0f, -camMoveSpeed);
        }
        */
        if (event.key.scancode == sf::Keyboard::Scan::Right) {
          camera_->ShiftBy(camMoveSpeed, 0.0f);
        }
        if (event.key.scancode == sf::Keyboard::Scan::Left) {
          camera_->ShiftBy(-camMoveSpeed, 0.0f);
        }
        if (event.key.scancode == sf::Keyboard::Scan::Space) {
          for (auto it = physicals_.begin(); it != physicals_.end(); ++it) {
            std::unique_ptr<Physical>& entity = *it;
            if (entity->Explodes()) {
              entity->SetHealth(0);
              AddExplosion(new Explosion(entity->GetPos().GetX() + 0.01f,
                                     entity->GetPos().GetY() + 0.01f),
                       500.0f);
              FileManager::PlaySound("explosion");
            }
          }
        }
    /*
        if (event.key.scancode == sf::Keyboard::Scan::Comma) {
          camera_->Zoom(1 - camZoomSpeed);
        }
        if (event.key.scancode == sf::Keyboard::Scan::Period) {
          camera_->Zoom(1 + camZoomSpeed);
        }
        */
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
      showPower_ = true;
    }

    if (event.type == sf::Event::MouseButtonReleased) {
      float vel = std::min(gunTimer_.getElapsedTime().asSeconds() / 2, 1.0f);
      if (!guns_.empty()) {
        Fire(vel);
      }
      showPower_ = false;
    }
  }

  for (auto it = physicals_.begin(); it != physicals_.end(); ++it) {
    over_ = true;

    bool deleted = false;
    std::unique_ptr<Physical>& entity = *it;
    if (entity->GetType() == Entity::EntityType::ENEMY && entity->GetHealth() > 0) {
      over_ = false;
      break;
    }
  }
}

void Level::RenderAmmo(sf::RenderWindow& window, std::unique_ptr<Gun>& gun,
                       const int& index) {
  sf::Sprite ammo = gun->CopySprite();
  switch (gun->GunType()) {
    case Gun::GunType::RIFLE:
      ammo.setPosition(70.0f, 20.0f + index * 40.0f);
      break;

    case Gun::GunType::LAUNCHER:
      ammo.setPosition(90.0f, 20.0f + index * 40.0f);
      break;

    default:
      throw std::exception();
  }
  ammo.setRotation(0.0f);
  ammo.setScale(sf::Vector2(0.5f, 0.5f));
  window.draw(ammo);
}

void Level::Render(sf::RenderWindow& window) {
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

  if (!guns_.empty()) {
    RenderEntity(guns_.back(), window);
  }

  for (auto it = physicals_.begin(); it != physicals_.end(); ++it) {
    bool deleted = false;
    std::unique_ptr<Physical>& entity = *it;

    if (entity->IsDead()) continue;

    RenderEntity(entity, window);

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
                                     entity->GetPos().GetY() + 0.01f),
                       500.0f);
          FileManager::PlaySound("explosion");
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
        RenderAmmo(window, gun, i);
        i++;
      } else if (!game_.IsMultiplayer()) {
        RenderAmmo(window, gun, i);
        i++;
      }
      n++;
    }

    pointsText_.setString(std::to_string(points_));
    window.draw(pointsText_);

    if (over_) {
      if (!win_) {
        for (auto it = guns_.begin(); it != guns_.end(); ++it) {
          std::unique_ptr<Gun>& entity = *it;
          AddPoints(entity.get()->GetPoints());
        }

        win_ = true;
        complete_.GetSprite().setPosition(600, 200);
        star1_.GetSprite().setPosition(320, 450);
        star2_.GetSprite().setPosition(600, 450);
        star3_.GetSprite().setPosition(880, 450);

        // std::cout << "max: " << maxPoints_ << std::endl;

        if ((float)points_ / maxPoints_ > 0.1f) {
          star1_.SetTexture("star");
        }

        if ((float)points_/maxPoints_ > 0.4f) {
          star2_.SetTexture("star");
        }

        if ((float)points_/maxPoints_ > 0.65f) {
          star3_.SetTexture("star");
        }
      }

      window.draw(complete_.GetSprite());
      window.draw(star1_.GetSprite());
      window.draw(star2_.GetSprite());
      window.draw(star3_.GetSprite());
    }

    if (showPower_) {
      int pow = std::min(gunTimer_.getElapsedTime().asMilliseconds() / 2, 1000);
      powerText_.setString(std::to_string(pow));
      powerText_.setColor(sf::Color(pow / 4, 250 - pow / 4, 0));
      window.draw(powerText_);
    }
  }
}