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

  void SetMultiplayer(bool multi);

  const bool& IsMultiplayer();

  Vector GetDimensions();

  bool GetMultiplayer();

 private:
  std::unique_ptr<GameView> currentView_ = nullptr;

  std::vector<sf::Sound*> onGoingSounds_;

  int windowWidth_;
  int windowHeight_;

  std::string playerName_;

  bool multiplayer_ = false;
};

#endif