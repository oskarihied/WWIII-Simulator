#include "game.hpp"

Game::Game(int w, int h) : windowWidth_(w), windowHeight_(h) {
  manager_.LoadTextures(textures_, "images");
  manager_.LoadSFX(sfx_, "sfx");
}

void Game::StartLevel(int levelIndex) {
  delete currentLevel_;

  std::string filename = "src/levels/level_" + std::to_string(levelIndex);

  currentLevel_ = manager_.LoadLevel(filename, textures_, sfx_, multiplayer_);
  for (int i = 0; i < 5; i++) {
    currentLevel_->AddGround(new Ground(i * 10, -1));
  }
  currentLevel_->GetCam()->MoveTo(20, 15);
  currentLevel_->GetCam()->ZoomTo(30);

  if (multiplayer_) {
    currentLevel_->GetCam()->NewAnimation(
        Pos(currentLevel_->CurrentGun()->GetPos().GetX() - 10, 7), 15, 2);
  } else {
    currentLevel_->GetCam()->NewAnimation(
        Pos(currentLevel_->CurrentGun()->GetPos().GetX() - 5, 7), 15, 2);
  }
}

void Game::StartMenu() {
  if (currentLevel_ != nullptr) {
    delete currentLevel_;
  }
  currentLevel_ = (Level*)new Menu(textures_, sfx_, windowWidth_);
}

Level* Game::GetCurrentLevel() { return currentLevel_; }

std::pair<int, int> Game::ToScreenPos(Pos pos, Camera cam) {
  float x = pos.GetX();
  float y = pos.GetY();

  x -= cam.GetPos().GetX();
  y -= cam.GetPos().GetY();

  x *= windowWidth_ / (cam.GetZoom());
  y *= windowWidth_ / (cam.GetZoom());

  return (std::pair((int)x, (int)y));
}

Pos Game::ToGamePos(int x, int y, Camera cam) {
  float posX = (x * (cam.GetZoom())) / windowWidth_ + cam.GetPos().GetX();
  float posY = (-y * (cam.GetZoom())) / windowWidth_ + cam.GetPos().GetY();

  return Pos(posX, posY);
}

sf::Texture& Game::GetTexture(std::string name) { return textures_.at(name); }

std::map<std::string, sf::Texture> Game::GetTextures() { return textures_; }

void Game::SetMultiplayer(bool multi) { multiplayer_ = multi; }
bool Game::GetMultiplayer() { return multiplayer_; }