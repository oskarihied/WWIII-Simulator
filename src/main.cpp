#include <SFML/Graphics.hpp>
#include <iostream>

#include "background.hpp"
#include "boxes.hpp"
#include "game.hpp"
#include "physics.hpp"

int main() {
  // Create the main window

  int w = 1300;
  int h = 700;

  Game game = Game(w, h);

  FileManager manager = FileManager();
  game.LoadTextures(manager);

  Level* level = game.startLevel();


  Level* menu = game.StartMenu();

  menu->AddNonPhysicalEntity(new Entity(4, 2.5, game.GetTexture("logo")));
  menu->AddButton(new Button(2, 0, 1, 1, game.GetTexture("button")));


  Level* currentLevel = game.GetCurrentLevel();

  // level->AddBox(new Concrete(3, 0, game));
  // level->AddBox(new Wood(4, 0, game));
  // level->AddBox(new Wood(5, 0, game));

  level->AddBox(new Wood(7, 0, game));
  level->AddBox(new Wood(7, 1, game));
  level->AddBox(new Wood(7, 2, game));
  level->AddBox(new Wood(7, 3, game));
  level->AddBox(new Wood(7, 4, game));
  level->AddBox(new Wood(7, 5, game));
  level->AddBox(new Wood(7, 6, game));
  level->AddBox(new Wood(7, 7, game));

  // level->AddBox(new Wood(4, 2, game));
  // level->AddBox(new Glass(4, 1, game));
  // level->AddBox(new Glass(5, 1, game));
  // level->AddBox(new Glass(6, 0, game));
  level->AddNonPhysicalEntity(new Entity(0, 0, game.GetTexture("trump")));

  // level->AddNonPhysicalEntity(new Entity(1.5, -0.2,
  // "images/rifle_bullet.png"));
  level->AddNonPhysicalEntity(new Entity(-1, 0, game.GetTexture("marin")));
  // level->AddNonPhysicalEntity(new Entity(-1, -0.2, "images/rifle.png"));
  level->AddNonPhysicalEntity(new Entity(-2, 0, game.GetTexture("putin")));
  level->AddNonPhysicalEntity(new Entity(-3, 0, game.GetTexture("kim")));
  level->AddNonPhysicalEntity(new Entity(-4, 0, game.GetTexture("xi")));
  level->AddNonPhysicalEntity(new Entity(-5, 0, game.GetTexture("biden")));

  // level->AddNonPhysicalEntity(new Entity(-2, -0.2, "images/rifle.png"));

  Entity* gun1 = new Entity(0, -0.2, game.GetTexture("rifle"));
  Entity* gun2 = new Entity(-1, -0.2, game.GetTexture("rifle"));
  Entity* gun3 = new Entity(-2, -0.2, game.GetTexture("rifle"));
  Entity* gun4 = new Entity(-3, -0.2, game.GetTexture("rifle"));
  Entity* gun5 = new Entity(-4, -0.2, game.GetTexture("rifle"));
  Entity* gun6 = new Entity(-5, -0.2, game.GetTexture("rifle"));
  // level->AddNonPhysicalEntity(level->CurrentGun());
  level->AddGun(gun1);
  level->AddGun(gun2);
  level->AddGun(gun3);
  level->AddGun(gun4);
  level->AddGun(gun5);
  level->AddGun(gun6);

  level->Fire();

  sf::RenderWindow window(sf::VideoMode(w, h), "WWIII Simulator");
  // b2Vec2 v = b2Vec2(4.5, 6.8);
  Physics* physics = currentLevel->GetPhysics();

  // physics->AddBox(new Box(1, 4000));
  level->AddGround(new Ground(0, -1));
  level->AddGround(new Ground(10, -1));

  window.setFramerateLimit(60);
  // Start the game loop
  while (window.isOpen()) {
    // Process events
    sf::Event event;

    // Advance simulation
    physics->SimulateWorld(1 / 60.0f);

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    Entity* currentGun = level->CurrentGun();

    std::pair<int, int> gunPos =
        game.ToScreenPos(currentGun->GetPos(), *currentLevel->GetCam());

    float gunY = -(float)mousePos.y - gunPos.second;
    float gunX = (float)mousePos.x - gunPos.first;

    // std::cout << gunX << std::endl;

    float gunRotation = -atan(gunY / gunX);

    if (gunX < 0) {
      gunRotation += M_PI;
    }

    // std::cout << gunRotation * (180.0f/M_PI) << std::endl;

    level->CurrentGun()->RotationTo(gunRotation * (180.0f / M_PI));
    gun2->RotationTo(gunRotation * (180.0f / M_PI));
    gun3->RotationTo(gunRotation * (180.0f / M_PI));
    gun4->RotationTo(gunRotation * (180.0f / M_PI));
    gun5->RotationTo(gunRotation * (180.0f / M_PI));
    gun6->RotationTo(gunRotation * (180.0f / M_PI));
    // gun3->RotationTo(gunRotation * (180.0f/M_PI));

    while (window.pollEvent(event)) {
      float speed = 0.5f;
      float zoomSpeed = 0.05f;

      if (event.type == sf::Event::KeyPressed) {
        if (event.key.scancode == sf::Keyboard::Scan::Up) {
          currentLevel->GetCam()->Move(0.0f, speed);
        }
        if (event.key.scancode == sf::Keyboard::Scan::Down) {
          currentLevel->GetCam()->Move(0.0f, -speed);
        }
        if (event.key.scancode == sf::Keyboard::Scan::Right) {
          currentLevel->GetCam()->Move(speed, 0.0f);
        }
        if (event.key.scancode == sf::Keyboard::Scan::Left) {
          currentLevel->GetCam()->Move(-speed, 0.0f);
        }
        
        if (event.key.scancode == sf::Keyboard::Scan::Comma) {
          currentLevel->GetCam()->Zoom(1 - zoomSpeed);
        }
        if (event.key.scancode == sf::Keyboard::Scan::Period) {
          currentLevel->GetCam()->Zoom(1 + zoomSpeed);
        }

        if (event.key.scancode == sf::Keyboard::Scan::Escape) {
          currentLevel = game.SwitchLevel(menu);
          physics = currentLevel->GetPhysics();
        }
      }

      if (event.type == sf::Event::MouseButtonPressed) {
        Pos gamePos = game.ToGamePos(mousePos.x, mousePos.y, *currentLevel->GetCam());
        for (Button* button : currentLevel->GetButtons()) {
          if (button->IsTouching(gamePos.GetX(), gamePos.GetY())) {
            currentLevel = game.SwitchLevel(level);
            physics = currentLevel->GetPhysics();
            //std::cout << "button" << std::endl;
          }
        }
      }

      // Close window: exit
      if (event.type == sf::Event::Closed) window.close();
    }
    // Clear screen
    window.clear();
    
    /*
    sf::Texture texture;
    texture.loadFromFile("images/background1.jpg");
    // std::cout << texture.loadFromFile("images/background.jpg") << std::endl;

    sf::Sprite background;
    background.setTexture(texture);
    background.setScale(sf::Vector2(2.0f, 2.0f));
    
    window.draw(background);
    */

    window.draw(currentLevel->GetBackground());
    

    for (Entity* entity : currentLevel->GetNonPhysicalEntities()) {
      float scale = (w / 200.0f) / currentLevel->GetCam()->GetZoom();

      entity->GetSprite()->setScale(sf::Vector2(scale, scale));
      entity->GetSprite()->setRotation(entity->GetRotation());

      std::pair<int, int> pos =
          game.ToScreenPos(entity->GetPos(), *currentLevel->GetCam());
      entity->GetSprite()->setPosition(pos.first, -pos.second);

      window.draw(*(entity->GetSprite()));
    }

    for (Entity* entity : physics->GetEntities()) {
      // std::cout << entity->GetSprite() << std::endl;

      float scale = (w / 200.0f) / currentLevel->GetCam()->GetZoom();

      entity->GetSprite()->setScale(sf::Vector2(scale, scale));
      entity->GetSprite()->setRotation(entity->GetRotation());

      std::pair<int, int> pos =
          game.ToScreenPos(entity->GetPos(), *currentLevel->GetCam());

      // std::cout << pos.first << " " << pos.second << std::endl;

      entity->GetSprite()->setPosition(pos.first, -pos.second);

      window.draw(*(entity->GetSprite()));
    }
    
    // std::cout << std::endl;
    // Update the window
    window.display();
  }

  return EXIT_SUCCESS;
}