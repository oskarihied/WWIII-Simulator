#ifndef MENU_HPP
#define MENU_HPP

#include "gameView.hpp"

class Menu : public GameView {
 public:
  Menu(Game& game);

  void StepInTime(sf::RenderWindow& window);

  void Render(sf::RenderWindow& window);
};

#endif