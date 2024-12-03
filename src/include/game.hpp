#ifndef GAME_HPP
#define GAME_HPP

#include <map>

#include "fileManager.hpp"
#include "level.hpp"
#include "menu.hpp"

class Game {
 public:
  Game(int w, int h);

  void StartLevel(int levelIndex);

  void StartMenu();

  Level* GetCurrentLevel();

  std::pair<int, int> ToScreenPos(Pos pos, Camera cam);
  Pos ToGamePos(int x, int y, Camera cam);

  std::vector<Entity*> LevelEntities() { return currentLevel_->GetEntities(); }

  sf::Texture& GetTexture(std::string name);
  std::map<std::string, sf::Texture> GetTextures();

  void SetMultiplayer(bool multi);

 private:
  std::string playerName_;
  Level* currentLevel_ = nullptr;

  int windowWidth_;
  int windowHeight_;

  std::map<std::string, sf::Texture> textures_;

  FileManager manager_ = FileManager();
  bool multiplayer_ = false;
};
#endif
