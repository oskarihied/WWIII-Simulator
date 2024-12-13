#ifndef GAMEVIEW_HPP
#define GAMEVIEW_HPP

#include <SFML/Graphics.hpp>

#include "button.hpp"
#include "camera.hpp"

class Game;

//Represents a view that is shown on a screen
//Has methods for rendering and checking buttons
class GameView {
 public:
  //params: current game
  GameView(Game& game);

  //virtual destructor
  virtual ~GameView() = 0;

  //Adds a new button to the gameview
  //params: pointer to the new button
  void AddButton(std::unique_ptr<Button> button);

  //Adds a new nonphysical entity to the gameview
  //params: pointer to the entity
  void AddNonPhysicalEntity(std::unique_ptr<Entity> entity);

  //returns: GameViews camera
  std::unique_ptr<Camera>& GetCam();

  //return lists of the buttons and nonphysicals in the scene
  std::vector<std::unique_ptr<Button>>& GetButtons();
  std::vector<std::unique_ptr<Entity>>& GetNonPhysicals();

  //renders an entity to the screen
  //params: entity, current window
  template <typename T>
  void RenderEntity(std::unique_ptr<T>& entity, sf::RenderWindow& window);

  //Progresses one step in the scene
  //params: current window
  virtual void StepInTime(sf::RenderWindow& window) = 0;

  //Draws the entities to the screen
  //params: current window
  virtual void Render(sf::RenderWindow& window) = 0;

 protected:
  //Game that is going on
  Game& game_;

  //Background image
  sf::Sprite background_;

  //Camera
  std::unique_ptr<Camera> camera_;

  //list of entities on the scene
  std::vector<std::unique_ptr<Entity>> nonPhysicals_;
  std::vector<std::unique_ptr<Button>> buttons_;
};

#endif