#ifndef MENU_HPP
#define MENU_HPP

#include "gameView.hpp"

//For starting the game and choosing level
class Menu : public GameView {
 public:
  //params: current game
  Menu(Game& game);

  //Progress one step in time
  //params: current window
  void StepInTime(sf::RenderWindow& window);

  //Draws sprites
  //params: current window
  void Render(sf::RenderWindow& window);
};

#endif