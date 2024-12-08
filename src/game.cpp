#include "game.hpp"

#include "menu.hpp"

Game::Game(int w, int h) : windowWidth_(w), windowHeight_(h) {
  FileManager::LoadTextures(textures_, "images");
  FileManager::LoadSFX(sfx_, "sfx");
}

std::unique_ptr<GameView>& Game::GetCurrentView() { return currentView_; }

void Game::StartMenu() {
  currentView_ = nullptr;
  currentView_.reset(new Menu(*this));
}

void Game::StartLevel(int levelIndex) {
  currentView_ = nullptr;

  std::string filename = "src/levels/level_" + std::to_string(levelIndex);

  std::unique_ptr<Level> level = FileManager::LoadLevel(filename, *this);
  for (int i = 0; i < 5; i++) {
    auto ground = std::make_unique<Ground>(i * 10, -1, textures_);
    level->AddGround(std::move(ground));
  }

  currentView_ = std::move(level);

  currentView_->GetCam()->MoveTo(20, 15);
  currentView_->GetCam()->ZoomTo(30);

  if (multiplayer_) {
    currentView_->GetCam()->NewAnimation(Vector(40 - 10, 7), 15, 2);
  } else {
    currentView_->GetCam()->NewAnimation(Vector(0 - 5, 7), 15, 2);
  }
}

Vector Game::ToScreenPos(Vector& gamePos, Camera cam) {
  float x = gamePos.GetX();
  float y = gamePos.GetY();

  x -= cam.GetPos().GetX();
  y -= cam.GetPos().GetY();

  x *= windowWidth_ / cam.GetZoom();
  y *= windowWidth_ / cam.GetZoom();

  return Vector(x, y);
}

Vector Game::ToGamePos(Vector& screenPos, Camera cam) {
  float x = screenPos.GetX();
  float y = screenPos.GetY();

  x *= cam.GetZoom() / windowWidth_;
  y *= -cam.GetZoom() / windowWidth_;

  x += cam.GetPos().GetX();
  y += cam.GetPos().GetY();

  return Vector(x, y);
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

const bool& Game::IsMultiplayer() { return multiplayer_; }