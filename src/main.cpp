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

  level->AddBox(new Concrete(3, 1));
  level->AddBox(new Wood(4, 0));
  level->AddBox(new Wood(4.5, 3));
  level->AddBox(new Glass(4, 5));
  level->AddBox(new Glass(5, 1));
  level->AddBox(new Glass(7.5, 4.6));
  level->AddNonPhysicalEntity(new Entity(0, 0, "images/trump.png"));
  level->AddNonPhysicalEntity(new Entity(0, -0.2, "images/rifle.png"));
  level->AddNonPhysicalEntity(new Entity(1.5, -0.2, "images/rifle_bullet.png"));
  level->AddNonPhysicalEntity(new Entity(-1, 0, "images/marin.png"));
  level->AddNonPhysicalEntity(new Entity(-1, -0.2, "images/rifle.png"));
  level->AddNonPhysicalEntity(new Entity(-2, 0, "images/putin.png"));
  level->AddNonPhysicalEntity(new Entity(-2, -0.2, "images/rifle.png"));

  sf::RenderWindow window(sf::VideoMode(w, h), "WWIII Simulator");
  // b2Vec2 v = b2Vec2(4.5, 6.8);
  Physics* physics = level->GetPhysics();

  physics->AddBox(new Box(1, 4000));
  physics->AddGround(new Ground());

  window.setFramerateLimit(60);
  // Start the game loop
  while (window.isOpen()) {
    // Process events
    sf::Event event;

    // Advance simulation
    physics->SimulateWorld(1 / 60.0f);

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


    for (Entity* entity : level->GetNonPhysicalEntities()) {
      float scale = (w / 200.0f) / level->GetCam()->GetZoom();

      entity->GetSprite()->setScale(sf::Vector2(scale, scale));

      std::pair<int, int> pos = game.ToScreenPos(entity->GetPos(), *level->GetCam());
      entity->GetSprite()->setPosition(pos.first, -pos.second);

      
      window.draw(*(entity->GetSprite()));

    }



    for (Entity* entity : physics->GetEntities()) {
      // std::cout << entity->GetSprite() << std::endl;

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