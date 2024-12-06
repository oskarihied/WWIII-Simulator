#include "game.hpp"

#include "menu.hpp"

Game::Game(int w, int h) : windowWidth_(w), windowHeight_(h) {
  manager_ = FileManager();
  manager_.LoadTextures(textures_, "images");
  manager_.LoadSFX(sfx_, "sfx");
}

void Game::StartLevel(int levelIndex) {
  currentView_ = nullptr;

  std::string filename = "src/levels/level_" + std::to_string(levelIndex);

  Level* level = manager_.LoadLevel(filename, *this);
  for (int i = 0; i < 5; i++) {
    auto ground = std::make_unique<Ground>(i * 10, -1, textures_);
    level->AddGround(std::move(ground));
  }

  currentView_.reset(level);

  currentView_->GetCam()->MoveTo(20, 15);
  currentView_->GetCam()->ZoomTo(30);

  if (multiplayer_) {
    currentView_->GetCam()->NewAnimation(Vector(40 - 10, 7), 15, 2);
  } else {
    currentView_->GetCam()->NewAnimation(Vector(0 - 5, 7), 15, 2);
  }
}

void Game::StartMenu() {
  if (currentView_.get() != nullptr) {
    currentView_ = nullptr;
  }
  currentView_.reset(new Menu(*this));
}

std::unique_ptr<GameView>& Game::GetCurrentView() { return currentView_; }

std::pair<int, int> Game::ToScreenPos(Vector pos, Camera cam) {
  float x = pos.GetX();
  float y = pos.GetY();

  x -= cam.GetPos().GetX();
  y -= cam.GetPos().GetY();

  x *= windowWidth_ / (cam.GetZoom());
  y *= windowWidth_ / (cam.GetZoom());

  return (std::pair((int)x, (int)y));
}

Vector Game::ToGamePos(int x, int y, Camera cam) {
  float posX = (x * (cam.GetZoom())) / windowWidth_ + cam.GetPos().GetX();
  float posY = (-y * (cam.GetZoom())) / windowWidth_ + cam.GetPos().GetY();

  return Vector(posX, posY);
}

sf::Texture& Game::GetTexture(const std::string name) {
  return textures_.at(name);
}

std::map<std::string, sf::Texture>& Game::GetTextures() { return textures_; }

void Game::PlaySound(const std::string name) {
  sf::Sound* sound = new sf::Sound(sfx_.at(name));
  sound->play();
  onGoingSounds_.push_back(sound);
}

std::vector<sf::Sound*>& Game::GetSounds() { return onGoingSounds_; }

void Game::SetMultiplayer(bool multi) { multiplayer_ = multi; }

bool Game::IsMultiplayer() { return multiplayer_; }