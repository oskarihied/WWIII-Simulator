#include <box2d/box2d.h>

#include <SFML/Graphics.hpp>
#include <iostream>

#include "background.hpp"
#include "boxes.hpp"
#include "game.hpp"
#include "physics.hpp"

int main() {
  // Create the main window

  int w = 1200;
  int h = 800;

  Game game = Game(w, h);

  Level* level = game.startLevel();

  level->AddBox(new Concrete(1, 1));
  level->AddBox(new Wood(1, 0));
  level->AddBox(new Wood(4.5, 3));
  level->AddBox(new Glass(2, 5));
  level->AddBox(new Glass(4, 1));

  sf::RenderWindow window(sf::VideoMode(w, h), "WWIII Simulator");
  // b2Vec2 v = b2Vec2(4.5, 6.8);
  Physics* physics = level->GetPhysics();

  physics->AddBox(new Box(1, 4000));
  physics->AddGround(new Ground());

  // Start the game loop
  while (window.isOpen()) {
    // Process events
    sf::Event event;

    // Advance simulation
    physics->SimulateWorld(0.01);

    while (window.pollEvent(event)) {
      
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.scancode == sf::Keyboard::Scan::Up) {
          level->GetCam()->Move(0.0f, 1.0f);
        }
        if (event.key.scancode == sf::Keyboard::Scan::Down) {
          level->GetCam()->Move(0.0f, -1.0f);
        }
        if (event.key.scancode == sf::Keyboard::Scan::Right) {
          level->GetCam()->Move(1.0f, 0.0f);
        }
        if (event.key.scancode == sf::Keyboard::Scan::Left) {
          level->GetCam()->Move(-1.0f, 0.0f);
        }
        if (event.key.scancode == sf::Keyboard::Scan::Comma) {
          level->GetCam()->Zoom(0.95);
        }
        if (event.key.scancode == sf::Keyboard::Scan::Period) {
          level->GetCam()->Zoom(1.05);
        }
        
      }

      // Close window: exit
      if (event.type == sf::Event::Closed) window.close();
    }
    // Clear screen
    window.clear();

    sf::Texture texture;
    texture.loadFromFile("images/background.jpg");
    // std::cout << texture.loadFromFile("images/background.jpg") << std::endl;

    sf::Sprite background;
    background.setTexture(texture);
    background.setScale(sf::Vector2(2.0f, 2.0f));

    window.draw(background);

    for (Entity* entity : physics->GetEntities()) {
      // std::cout << entity->GetSprite() << std::endl;
      Pos pos2 = entity->GetPos();
      Pos pos3 = pos2;
      pos3.Add(1, 0);
      pos2.GetX();

      float scale = (w / 200.0f) / level->GetCam()->GetZoom();

      entity->GetSprite()->setScale(sf::Vector2(scale, scale));
      entity->GetSprite()->setRotation(entity->GetRotation());

      std::pair<int, int> pos = game.ToScreenPos(entity->GetPos(), *level->GetCam());
      entity->GetSprite()->setPosition(pos.first, -pos.second);

      
      window.draw(*(entity->GetSprite()));

    }

    // Update the window
    window.display();
  }

  return EXIT_SUCCESS;
}