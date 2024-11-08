#include <box2d/box2d.h>

#include <SFML/Graphics.hpp>
#include <iostream>

#include "game.hpp"
#include "background.hpp"
#include "boxes.hpp"

#include "physics.hpp"

int main() {
  // Create the main window

  int w = 1000;
  int h = 800;

  Game game = Game(w, h);

  Level* level = game.startLevel();

  std::pair<int, int> pos = game.ToScreenPos(Pos(1, 1), level->GetCam());

  //Background background = Background("background.jpg");

  Box box = Concrete(-5, 3);
  
  //std::cout << box.GetSprite() << std::endl;

  level->AddBox(&box);
  level->AddBox(new Wood(0, 3));
  level->AddBox(new Glass(0, 6));

  std::cout << "pos: " << pos.first << " " << pos.second << std::endl << std::endl << std::endl;

  sf::RenderWindow window(sf::VideoMode(w, h), "WW-III Simulator");
  //b2Vec2 v = b2Vec2(4.5, 6.8);
  Physics* physics = level->GetPhysics();
  
  physics->AddBox( new Box(1, 4000));
  physics->AddGround( new Ground());

  // Start the game loop
  while (window.isOpen()) {
    // Process events
    sf::Event event;
    
    // Advance simulation
    physics->SimulateWorld(0.002);

    while (window.pollEvent(event)) {
      // Close window: exit

      if (event.type == sf::Event::Closed) window.close();
    }
    // Clear screen
    window.clear();

    sf::Texture texture;
    texture.loadFromFile("images/background.jpg");
    //std::cout << texture.loadFromFile("images/background.jpg") << std::endl;

    sf::Sprite sprite;
    sprite.setTexture(texture);

    window.draw(sprite);

    for (Entity* entity : physics->GetEntities()) {
      //std::cout << entity->GetSprite() << std::endl;
      float scale = 1.0f / level->GetCam().GetZoom() * 5;
      //entity->GetSprite()->setScale(sf::Vector2(scale, scale));

      std::pair<int, int> pos = game.ToScreenPos(entity->GetPos(), level->GetCam());
      entity->GetSprite()->setOrigin(pos.first, pos.second);

      entity->GetSprite()->setScale(sf::Vector2(scale, scale));
    
      window.draw(*(entity->GetSprite()));


      //std::cout << entity->GetImage() << " pos: " << entity->GetPos().GetX() << " " << entity->GetPos().GetY() << " screen: " << pos.first << " " << pos.second << std::endl;
    }

    for (b2Body* body : physics->GetBodies()) {
      //std::cout << "physic: " << body->GetPosition().x << " " << body->GetPosition().y << std::endl;
    }



    // Update the window
    window.display();
  }

  return EXIT_SUCCESS;
}