#ifndef GAME_HPP
#define GAME_HPP

#include <map>

#include "fileManager.hpp"
#include "gameView.hpp"

class Game {
 public:
  Game(int w, int h);

  void StartLevel(int levelIndex);

  void StartMenu();

  std::unique_ptr<GameView>& GetCurrentView();

  std::pair<int, int> ToScreenPos(Vector pos, Camera cam);
  Vector ToGamePos(int x, int y, Camera cam);

  sf::Texture& GetTexture(const std::string name);
  std::map<std::string, sf::Texture> GetTextures();

  void PlaySound(const std::string name);

  std::vector<sf::Sound*>& GetSounds();

  void SetMultiplayer(bool multi);

  bool IsMultiplayer();

 private:
  std::string playerName_;

  FileManager manager_;

  std::unique_ptr<GameView> currentView_ = nullptr;

  int windowWidth_;
  int windowHeight_;

  std::map<std::string, sf::Texture> textures_;
  std::map<std::string, sf::SoundBuffer> sfx_;

  std::vector<sf::Sound*> onGoingSounds_;

  bool multiplayer_ = false;
};

#endif