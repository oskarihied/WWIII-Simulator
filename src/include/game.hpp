#ifndef GAME_HPP
#define GAME_HPP

#include <map>

#include "fileManager.hpp"
#include "gameView.hpp"

class Game {
 public:
  Game(int w, int h);

  std::unique_ptr<GameView>& GetCurrentView();

  void StartMenu();
  void StartLevel(int levelIndex);

  Vector ToScreenPos(Vector& gamePos, Camera cam);
  Vector ToGamePos(Vector& screenPos, Camera cam);

  sf::Texture& GetTexture(const std::string name);

  std::map<std::string, sf::Texture>& GetTextures();

  void PlaySound(const std::string name);

  std::vector<sf::Sound*>& GetSounds();

  void SetMultiplayer(bool multi);

  const bool& IsMultiplayer();

 private:
  std::unique_ptr<GameView> currentView_ = nullptr;

  std::map<std::string, sf::Texture> textures_;
  std::map<std::string, sf::SoundBuffer> sfx_;

  std::vector<sf::Sound*> onGoingSounds_;

  int windowWidth_;
  int windowHeight_;

  std::string playerName_;

  bool multiplayer_ = false;
};

#endif