#include "level.hpp"

#include <exception>

#include "game.hpp"

Level::Level(Game& game) : GameView(game) {
  //Setup physics
  physics_ = std::make_unique<Physics>(physicals_);

  //setup background
  background_.setTexture(*FileManager::GetTexture("background1"));
  background_.setScale(1.0f, 1.0f);

  //UI text setup
  font_.loadFromFile("fonts/AmericanTypewriter.ttc");
  pointsText_.setFont(font_);
  pointsText_.setString("0");
  pointsText_.setCharacterSize(50);
  pointsText_.setPosition(200, 0);

  powerText_.setFont(font_);
  powerText_.setString("0");
  powerText_.setCharacterSize(50);
  powerText_.setPosition(200, 70);

  //UI setup
  complete_.SetTexture("mission_complete");
  star1_.SetTexture("star_black");
  star2_.SetTexture("star_black");
  star3_.SetTexture("star_black");
  winner_.SetTexture("plr1_wins");
}

void Level::AddScore(std::string name, int score) {
  leaderboard_.push_back(std::make_pair(name, score));
}

void Level::AddScores(std::vector<std::pair<std::string, int>> scores) {
  for (auto it : scores) {
    leaderboard_.push_back(it);
  }
}

void Level::Fire(float speed) {
  std::unique_ptr<Gun>& currentGun = guns_.back();

  //check if currentGun exists
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

    //Set bullet transforms
    b->MoveTo(b->GetPos().GetX() + x, b->GetPos().GetY() + y);
    b->UpdateVel(x * speed * 30, y * speed * 30);
    b->RotationTo(gunRot);

    //add bullet body
    physics_->AddBoxBody(b);
    currentBullet_ = b.get();
    physicals_.push_back(std::move(b));

    //Remove gun
    guns_.pop_back();
    if (!guns_.empty()) {
      guns_.back()->RotationTo(gunRot);
    }

    timer_ = 0;
    bulletTimer_ = true;
  }
}

std::vector<std::pair<std::string, int>> Level::GetLeaderboard() {
  return leaderboard_;
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

void Level::AddPoints(int points) { points_ += points; }

void Level::AddMaxPoints(int points) { maxPoints_ += points; }

int Level::GetPoints() { return points_; }

void Level::AddExplosion(std::unique_ptr<Explosion> explosion, float force) {
  Vector& pos = explosion->GetPos();
  explosions_.push_back(std::move(explosion));
  physics_->SpawnExplosion(pos, force);
  FileManager::PlaySound("explosion");
}

std::vector<std::unique_ptr<Physical>>& Level::GetPhysicals() {
  return physicals_;
}

std::vector<std::unique_ptr<Gun>>& Level::GetGuns() { return guns_; }

const bool& Level::IsMultiplayer() { return game_.IsMultiplayer(); }

void Level::StepInTime(sf::RenderWindow& window) {
  //Steps the physics take during one frame
  float subSteps = 4;
  float step = 1.0f / 60.0f / subSteps;
  for (int i = 0; i < subSteps; ++i) {
    //Simulate world in physics
    physics_->SimulateWorld(step);
  }
  //move camera
  camera_->AnimationStep(1.0f / 60.0f);

  sf::Event event;
  sf::Vector2i mousePos = sf::Mouse::getPosition(window);

  //bullet follow animation
  if (GetTimer() > 0 && GetTimer() <= 2 && !currentBullet_->IsDead()) {
    camera_->MoveTo(currentBullet_->GetPos().GetX() - 5,
                    camera_->GetPos().GetY());
  }
  IncrementBulletTimer(1.0f / 60.0f);

  //Change currentGun
  if (!guns_.empty()) {
    std::unique_ptr<Gun>& currentGun = guns_.back();

    if (GetTimer() > 2) {
      SetTimer(false);
      Vector v;

      //Animation back to the gunner
      if (currentGun->GetPos().GetX() == 0) {
        v = Vector(currentGun->GetPos().GetX() - 5, 12);
        camera_->NewAnimation(v, 25, 2);
      } else {
        v = Vector(currentGun->GetPos().GetX() - 10, 12);
        camera_->NewAnimation(v, 25, 2);
      }
    }

    //Calculate gun rotation based on mouse position
    Vector gunPos = game_.ToScreenPos(currentGun->GetPos(), *camera_);
    float gunY = -(float)mousePos.y - gunPos.GetY();
    float gunX = (float)mousePos.x - gunPos.GetX();
    float gunRotation = atan(gunY / gunX);
    
    //Set gun rotation
    if (gunX < 0) {
      if (gunY < 0) {
        gunRotation = -M_PI + gunRotation;
      } else {
        gunRotation = M_PI + gunRotation;
      }
    }
    currentGun->RotationTo(gunRotation * (180.0f / M_PI));
  }

  //Go through physicals to check health
  for (auto& physical : physicals_) {
    bool deleted = false;

    if (physical->IsDead()) {
      continue;
    }

    //Change texture if needed
    physical->BecomeDamaged();

    if (physical->GetHealth() <= 0) {
      //Breaking sound
      FileManager::PlaySound(physical->GetSound());
      physical->Die();
      //add points
      AddPoints(physical->GetPoints());

      //Do the explosion
      if (physical->Explodes()) {
        //Shift the explosion a bit to prevent dividing by zero
        float x = physical->GetPos().GetX() + 0.01f;
        float y = physical->GetPos().GetY() + 0.01f;
        auto explosion = std::make_unique<Explosion>(x, y);
        AddExplosion(std::move(explosion), 500.0f);
        physical->SetExplodes(false);
      }

      if (physical->IsDynamic()) {
        deleted = true;
        physics_->RemovePhysicalEntity(physical);
      }
    }
  }

  //Check for win condition
  for (auto& physical : physicals_) {
    over_ = true;
    if (physical->GetType() == Entity::EntityType::ENEMY &&
        !physical->IsDead() && !physical->GetSide()) {
      over_ = false;
      break;
    }
  }

  //Win condition check for multiplayer
  if (IsMultiplayer()) {
    for (auto& physical : physicals_) {
      over2_ = true;

      if (physical->GetType() == Entity::EntityType::ENEMY &&
          !physical->IsDead() && physical->GetSide()) {
        over2_ = false;
        break;
      }
    }
  }

  //Input handling
  while (window.pollEvent(event)) {
    float camMoveSpeed = 2.0f;
    //Check keys
    if (event.type == sf::Event::KeyPressed) {
      //Cannot move during animation
      if (!camera_->GetAnimation()) {
        //Movement
        if (event.key.scancode == sf::Keyboard::Scan::Right) {
          camera_->ShiftBy(camMoveSpeed, 0.0f);
        }
        if (event.key.scancode == sf::Keyboard::Scan::Left) {
          camera_->ShiftBy(-camMoveSpeed, 0.0f);
        }
        //explode with space
        if (event.key.scancode == sf::Keyboard::Scan::Space) {
          for (auto& physical : physicals_) {
            if (physical->Explodes()) {
              physical->Die();
              float x = physical->GetPos().GetX() + 0.01f;
              float y = physical->GetPos().GetY() + 0.01f;
              auto explosion = std::make_unique<Explosion>(x, y);
              AddExplosion(std::move(explosion), 500.0f);
              physical->SetExplodes(false);
              break;
            }
          }
        }
      }
    }

    //Check if esc is released
    if (event.type == sf::Event::KeyReleased) {
      if (event.key.scancode == sf::Keyboard::Scan::Escape) {
        //goes to menu
        game_.SetMultiplayer(false);
        game_.StartMenu();
      }
    }

    //Check if mouse is pressed
    if (event.type == sf::Event::MouseButtonPressed) {
      //starts gun Timer
      gunTimer_.restart();
      showPower_ = true;
    }

    //Or released
    if (event.type == sf::Event::MouseButtonReleased) {
      //Calculates power and fires
      float vel = std::min(gunTimer_.getElapsedTime().asSeconds() / 2, 1.0f);
      if (!guns_.empty()) {
        Fire(vel);
      }
      showPower_ = false;
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
  //Draws the gun to the corner
  ammo.setRotation(0.0f);
  ammo.setScale(sf::Vector2(0.5f, 0.5f));
  window.draw(ammo);
}

void Level::Render(sf::RenderWindow& window) {
  window.draw(background_);

  //changes next texture
  for (auto& explosion : explosions_) {
    if (explosion->GetCount() <= 10) {
      RenderEntity(explosion, window);
      explosion->NextSprite();
    }
  }

  //Renders nonphysicals
  for (std::unique_ptr<Entity>& entity : nonPhysicals_) {
    RenderEntity(entity, window);
  }

  //Renders guns
  if (!guns_.empty()) {
    RenderEntity(guns_.back(), window);
  }

  //Renders physicals
  for (std::unique_ptr<Physical>& physical : physicals_) {
    if (!physical->IsDead()) {
      RenderEntity(physical, window);
    }
  }

  //Renders guns left
  int n = 0;
  int i = 0;
  for (std::unique_ptr<Gun>& gun : guns_) {
    //Doesn't render guns twice in multiplayer
    if (game_.IsMultiplayer() && n % 2 == 0) {
      RenderAmmo(window, gun, i);
      i++;
    } else if (!game_.IsMultiplayer()) {
      RenderAmmo(window, gun, i);
      i++;
    }
    n++;
  }

  //Draw points
  pointsText_.setString(std::to_string(points_));
  window.draw(pointsText_);

  //Check if the game is over
  if (over_ || over2_) {
    if (!win_) {
      win_ = true;
    
      if (over2_) {
        winner_.SetTexture("plr2_wins");
      }
      
      //Victory sound
      FileManager::PlaySound("victory1");

      //Adds points from guns left
      for (auto& gun : guns_) {
        AddPoints(gun.get()->GetPoints());
      }

      //Update UI positions
      winner_.GetSprite().setPosition(700, 300);
      complete_.GetSprite().setPosition(600, 200);
      star1_.GetSprite().setPosition(320, 450);
      star2_.GetSprite().setPosition(600, 450);
      star3_.GetSprite().setPosition(880, 450);

      //Calculate stars
      if ((float)points_ / maxPoints_ > 0.1f) {
        star1_.SetTexture("star");
      }
      if ((float)points_ / maxPoints_ > 0.4f) {
        star2_.SetTexture("star");
      }
      if (((float)points_ + 500) / maxPoints_ > 0.65f) {
        star3_.SetTexture("star");
      }
    }

    //Different end screens in singleplayer and multiplayer
    if (!game_.IsMultiplayer()) {
      window.draw(complete_.GetSprite());
      window.draw(star1_.GetSprite());
      window.draw(star2_.GetSprite());
      window.draw(star3_.GetSprite());
    } else {
      window.draw(winner_.GetSprite());
    }
  }

  if (showPower_) {
    //Calculate power and render
    int pow = std::min(gunTimer_.getElapsedTime().asMilliseconds() / 2, 1000);
    powerText_.setString(std::to_string(pow));
    powerText_.setFillColor(sf::Color(pow / 4, 250 - pow / 4, 0));
    window.draw(powerText_);
  }
}