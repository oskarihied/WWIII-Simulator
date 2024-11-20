#include "game.hpp"

Game::Game(int w, int h) : windowWidth_(w), windowHeight_(h) {}

Level* Game::startLevel() {
  currentLevel_ = new Level(this->GetTexture("background1"));
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

Level* Game::GetCurrentLevel() {
  return currentLevel_;
}

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

sf::Texture& Game::GetTexture(std::string name) { return textures_.at(name); }
