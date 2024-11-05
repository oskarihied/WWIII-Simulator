#include <box2d/box2d.h>

#include <SFML/Graphics.hpp>
#include <iostream>

#include "game.hpp"
#include "background.hpp"

#include "physics.hpp"

int main() {
  // Create the main window

  int w = 800;
  int h = 600;

  Game game = Game(w, h);

  Level level = game.startLevel();

  std::pair<int, int> pos = game.ToScreenPos(Pos(1, 1), level.GetCam());

  Background background = Background("background.jpg");

  level.AddEntity((Entity &)background);

  std::cout << "pos: " << pos.first << " " << pos.second << std::endl << std::endl << std::endl;

  sf::RenderWindow window(sf::VideoMode(800, 600), "WW-III Simulator");
  //b2Vec2 v = b2Vec2(4.5, 6.8);
  Physics physics;
  
  physics.AddBox(Box(1, 4000));
  physics.AddGround(Ground());

  // Start the game loop
  while (window.isOpen()) {
    // Process events
    sf::Event event;
    
    // Advance simulation
    physics.SimulateWorld(0.002);

    while (window.pollEvent(event)) {
      // Close window: exit

      if (event.type == sf::Event::Closed) window.close();
    }
    // Clear screen
    window.clear();

    sf::Texture texture;
    std::cout << texture.loadFromFile("src/background.jpg") << std::endl;

    sf::Sprite sprite;
    sprite.setTexture(texture);

    window.draw(sprite);



    for (auto entity : level.GetEntities()) {
      std::cout << "hello" << std::endl;
      window.draw(entity.GetSprite());
    }

    // Update the window
    window.display();
  }

  return EXIT_SUCCESS;
}