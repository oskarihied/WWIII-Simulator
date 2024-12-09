#ifndef GAMEVIEW_HPP
#define GAMEVIEW_HPP

#include <SFML/Graphics.hpp>

#include "button.hpp"
#include "camera.hpp"

class Game;

class GameView {
 public:
  GameView(Game& game);

  void AddButton(std::unique_ptr<Button> button);
  void AddNonPhysicalEntity(std::unique_ptr<Entity> entity);

  std::unique_ptr<Camera>& GetCam();

  std::vector<std::unique_ptr<Button>>& GetButtons();
  std::vector<std::unique_ptr<Entity>>& GetNonPhysicals();

  template <typename T>
  void RenderEntity(std::unique_ptr<T>& entity, sf::RenderWindow& window);

  virtual void StepInTime(sf::RenderWindow& window) = 0;

  virtual void Render(sf::RenderWindow& window) = 0;

 protected:
  Game& game_;

  sf::Sprite background_;

  std::unique_ptr<Camera> camera_;

  std::vector<std::unique_ptr<Entity>> nonPhysicals_;
  std::vector<std::unique_ptr<Button>> buttons_;
};

#endif