#include "game.hpp"

Game::Game(int w, int h) : windowWidth_(w), windowHeight_(h) {}

Level* Game::StartLevel() {
  currentLevel_ = new Level(this->GetTexture("background1"));
  currentLevel_->GetCam()->MoveTo(20, 15);
  currentLevel_->GetCam()->ZoomTo(30);
  currentLevel_->GetCam()->NewAnimation(Pos(-5, 7), 15, 2);
  return currentLevel_;
}

Level* Game::StartMenu() {
  currentLevel_ = (Level*)(new Menu(this->GetTexture("menu")));
  return currentLevel_;
}

Level* Game::SwitchLevel(Level* level) {
  currentLevel_ = level;
  return currentLevel_;
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

void Game::LoadTextures(FileManager& manager) {
  manager.LoadTextures(textures_, "images");
  /*
    for (auto texture : textures_) {
      std::cout << texture.first << std::endl;
    }
    */
};

void Game::LoadLevel(FileManager& manager, Level* level) {
  /*currentLevel_->AddBoxes(manager.LoadLevel("src/levels/level_1", textures_));*/
  manager.LoadLevel("src/levels/level_1", textures_, level);
}

sf::Texture& Game::GetTexture(std::string name) { return textures_.at(name); }

std::map<std::string, sf::Texture> Game::GetTextures() { return textures_; }

void Game::SetMultiplayer(bool multi) { multiplayer_ = multi; }