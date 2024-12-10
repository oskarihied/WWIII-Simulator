#include "game.hpp"

#include "menu.hpp"

Game::Game(int w, int h) : windowWidth_(w), windowHeight_(h) {
  FileManager::LoadMusic("music");
  FileManager::LoadTextures("images");
  FileManager::LoadSFX("sfx");
  FileManager::PlayMusic("war-of-victory-2");
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
  for (int i = 0; i < 15; i++) {
    for (int j = 0; j < 5; j++) {
      auto ground = std::make_unique<Ground>(-20.0f + i * 10.0f, -1.5f - j * 2.0f);
      level->AddPhysical(std::move(ground));
    }
  }

  currentView_ = std::move(level);

  currentView_->GetCam()->MoveTo(20, 20);
  currentView_->GetCam()->ZoomTo(40);

  if (multiplayer_) {
    currentView_->GetCam()->NewAnimation(Vector(40 - 10, 12), 25, 2);
  } else {
    currentView_->GetCam()->NewAnimation(Vector(0 - 5, 12), 25, 2);
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

void Game::SetMultiplayer(bool multi) { multiplayer_ = multi; }

const bool& Game::IsMultiplayer() { return multiplayer_; }

Vector Game::GetDimensions() { return Vector(windowWidth_, windowHeight_); }