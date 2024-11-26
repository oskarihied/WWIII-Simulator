#ifndef GAME_HPP
#define GAME_HPP

#include <map>

#include "fileManager.hpp"
#include "level.hpp"
#include "menu.hpp"

class Game {
 public:
  Game(int w, int h);

  Level* startLevel();
  Level* StartMenu();

  Level* SwitchLevel(Level* level);

  Level* GetCurrentLevel();

  std::pair<int, int> ToScreenPos(Pos pos, Camera cam);
  Pos ToGamePos(int x, int y, Camera cam);

  std::vector<Entity*> levelEntities() { return currentLevel_->GetEntities(); }

  void LoadTextures(FileManager& manager);

  sf::Texture& GetTexture(std::string name);
  std::map<std::string, sf::Texture> GetTextures();

 private:
  std::string playerName_;
  Level* currentLevel_;

  int windowWidth_;
  int windowHeight_;

  std::map<std::string, sf::Texture> textures_;
};
#endif
