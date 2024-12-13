#ifndef GAME_HPP
#define GAME_HPP

#include <map>

#include "fileManager.hpp"
#include "gameView.hpp"

//Represents a single Game
//Responsible for creating levels and menus
class Game {
 public:
  //params: screen width and height
  Game(int w, int h);

  //returns: current GameView that is showing
  std::unique_ptr<GameView>& GetCurrentView();

  //starts a new menu
  void StartMenu();
  //starts a new level
  //params: index of the level. Currently 1-3
  void StartLevel(int levelIndex);

  //Calculates screen coordinates from game coordinates
  //params: position in the game, camera
  Vector ToScreenPos(Vector& gamePos, Camera cam);

  //Calculates game pos from a screen position
  //params: position on screen, camera
  Vector ToGamePos(Vector& screenPos, Camera cam);

  //params: multiplayer on(true)/off(false)
  void SetMultiplayer(bool multi);

  //returns: whether multiplayer if on or off
  const bool& IsMultiplayer();

  //returns: width and height of the window
  Vector GetDimensions();

 private:
  //GameView that is showing
  std::unique_ptr<GameView> currentView_ = nullptr;

  //list of sounds that are happening
  std::vector<sf::Sound*> onGoingSounds_;

  //screen dimensions
  int windowWidth_;
  int windowHeight_;

  //name of the player
  std::string playerName_;

  //multiplayer on/off
  bool multiplayer_ = false;
};

#endif