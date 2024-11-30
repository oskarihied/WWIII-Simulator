#include <SFML/Graphics.hpp>
#include <iostream>

#include "background.hpp"
#include "boxes.hpp"
#include "game.hpp"
#include "physics.hpp"
// #include "guns.hpp"

int main() {
  // Create the main window

  int w = 1300;
  int h = 700;

  Game game = Game(w, h);
  sf::Clock timer;

  FileManager manager = FileManager();
  game.LoadTextures(manager);

  Level* level = game.StartLevel();

  Level* menu = game.StartMenu();

  menu->AddNonPhysicalEntity(new Entity(4, 2.5, game.GetTexture("logo")));
  
  menu->AddButton(new Button(2, 0, 1, 1, game.GetTexture("button1")));
  menu->AddButton(new Button(4, 0, 1, 1, game.GetTexture("button2")));
  menu->AddButton(new Button(6, 0, 1, 1, game.GetTexture("button3")));


  Level* currentLevel = game.GetCurrentLevel();

  // level->AddBox(new Concrete(3, 0, game));
  // level->AddBox(new Wood(4, 0, game));
  // level->AddBox(new Wood(5, 0, game));
  /*
    level->AddBox(new Wood(7, 0, game));
    level->AddBox(new Wood(7, 1, game));
    level->AddBox(new Wood(7, 2, game));
    level->AddBox(new Wood(7, 3, game));
    level->AddBox(new Wood(7, 4, game));
    level->AddBox(new Wood(7, 5, game));
    level->AddBox(new Wood(7, 6, game));
    level->AddBox(new Wood(7, 7, game));
    level->AddBox(new Wood(8, 0, game));
    level->AddBox(new Wood(8, 1, game));
    level->AddBox(new Wood(8, 2, game));
    level->AddBox(new Wood(8, 3, game));
    level->AddBox(new Wood(8, 4, game));
    level->AddBox(new Wood(8, 5, game));
    level->AddBox(new Wood(8, 6, game));
    level->AddBox(new Wood(8, 7, game));
    */

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      level->AddBox(new Wood(7 + i, j, game.GetTextures()));
    }
  }

  level->AddEnemy(new Enemy(6, 0, game.GetTextures()));

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
  Gun* gun1 = new RocketLauncher(0, -0.2, game.GetTextures());
  Gun* gun2 = new RocketLauncher(0, -0.2, game.GetTextures());
  Gun* gun3 = new Rifle(0, -0.2, game.GetTextures());
  Gun* gun4 = new Rifle(0, -0.2, game.GetTextures());
  Gun* gun5 = new Rifle(0, -0.2, game.GetTextures());
  Gun* gun6 = new Rifle(0, -0.2, game.GetTextures());

  // level->AddNonPhysicalEntity(level->CurrentGun());

  level->AddGun(gun2);
  level->AddGun(gun3);
  level->AddGun(gun4);
  level->AddGun(gun5);
  level->AddGun(gun6);
  level->AddGun(gun1);

  // b2Vec2 v = b2Vec2(4.5, 6.8);
  Physics* physics = currentLevel->GetPhysics();

  sf::RenderWindow window(sf::VideoMode(w, h), "WWIII Simulator",
                          sf::Style::Fullscreen);

  // physics->AddBox(new Box(1, 4000));
  level->AddGround(new Ground(0, -1));
  level->AddGround(new Ground(10, -1));

  window.setFramerateLimit(60);
  // Start the game loop
  while (window.isOpen()) {
    // Process events
    sf::Event event;

    bool inMenu = currentLevel->IsMenu();

    std::vector<Entity*> nonPhysicals = currentLevel->GetNonPhysicalEntities();

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    if (!inMenu) {
      // Advance simulation
      physics->SimulateWorld(1.0f / 60.0f);
      currentLevel->GetCam()->AnimationStep(1.0f / 60.0f);

      Entity* gun = currentLevel->CurrentGun();

      if (gun) {
        std::pair<int, int> gunPos =
            game.ToScreenPos(gun->GetPos(), *currentLevel->GetCam());

        float gunY = -(float)mousePos.y - gunPos.second;
        float gunX = (float)mousePos.x - gunPos.first;

        float gunRotation = atan(gunY / gunX);
        if (gunX < 0) {
          if (gunY < 0) {
            gunRotation = -M_PI + gunRotation;
          } else {
            gunRotation = M_PI + gunRotation;
          }
        }

        currentLevel->CurrentGun()->RotationTo(-gunRotation * (180.0f / M_PI));

        nonPhysicals.push_back(gun);
      }
    }

    while (window.pollEvent(event)) {
      if (inMenu) {
        if (event.type == sf::Event::MouseButtonReleased) {
          Pos gamePos =
              game.ToGamePos(mousePos.x, mousePos.y, *currentLevel->GetCam());
          for (Button* button : currentLevel->GetButtons()) {
            if (button->IsTouching(gamePos.GetX(), gamePos.GetY())) {
              currentLevel = game.SwitchLevel(level);
              physics = currentLevel->GetPhysics();
            }
          }
        }

        if (event.key.scancode == sf::Keyboard::Scan::Escape) {
          window.close();
        }
      } else {
        float camMoveSpeed = 0.5f;
        float camZoomSpeed = 0.05f;

        if (event.type == sf::Event::KeyPressed) {
          if (!currentLevel->GetCam()->GetAnimation()) {
            if (event.key.scancode == sf::Keyboard::Scan::Up) {
              currentLevel->GetCam()->Move(0.0f, camMoveSpeed);
            }
            if (event.key.scancode == sf::Keyboard::Scan::Down) {
              currentLevel->GetCam()->Move(0.0f, -camMoveSpeed);
            }
            if (event.key.scancode == sf::Keyboard::Scan::Right) {
              currentLevel->GetCam()->Move(camMoveSpeed, 0.0f);
            }
            if (event.key.scancode == sf::Keyboard::Scan::Left) {
              currentLevel->GetCam()->Move(-camMoveSpeed, 0.0f);
            }

            if (event.key.scancode == sf::Keyboard::Scan::Comma) {
              currentLevel->GetCam()->Zoom(1 - camZoomSpeed);
            }
            if (event.key.scancode == sf::Keyboard::Scan::Period) {
              currentLevel->GetCam()->Zoom(1 + camZoomSpeed);
            }

          }
        }

        if (event.type == sf::Event::KeyReleased) {
          if (event.key.scancode == sf::Keyboard::Scan::Escape) {
            currentLevel = game.SwitchLevel(menu);
            physics = currentLevel->GetPhysics();
          }
        }

        if (event.type == sf::Event::MouseButtonPressed) {
          timer.restart();
        }

        if (event.type == sf::Event::MouseButtonReleased) {
          float vel = std::min(timer.getElapsedTime().asSeconds(), 2.0f);
          currentLevel->Fire(vel);
        }
      }
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

    for (Explosion* explosion : currentLevel->GetExplosions()) {
      explosion->NextSprite();
      if (explosion->GetCount() > 10) {
        currentLevel->RemoveExplosion(explosion);
      }
      // currentLevel->RemoveNonPhysicalEntity(explosion);
    }

    for (Entity* entity : nonPhysicals) {
      float scale = (w / 200.0f) / currentLevel->GetCam()->GetZoom();

      entity->GetSprite()->setScale(sf::Vector2(scale, scale));
      entity->GetSprite()->setRotation(entity->GetRotation());

      std::pair<int, int> pos =
          game.ToScreenPos(entity->GetPos(), *currentLevel->GetCam());
      entity->GetSprite()->setPosition(pos.first, -pos.second);

      window.draw(*(entity->GetSprite()));
    }

    if (!inMenu) {
      for (Entity* entity : physics->GetEntities()) {
        // std::cout << entity->GetSprite() << std::endl;

        float scale = (w / 200.0f) / currentLevel->GetCam()->GetZoom();

        entity->GetSprite()->setScale(sf::Vector2(scale, scale));
        entity->GetSprite()->setRotation(-entity->GetRotation());

        std::pair<int, int> pos =
            game.ToScreenPos(entity->GetPos(), *currentLevel->GetCam());

        // std::cout << entity->GetHealth() << std::endl;

        entity->GetSprite()->setPosition(pos.first, -pos.second);

        window.draw(*(entity->GetSprite()));

        if (entity->GetHealth() <= entity->GetMaxHealth() * 0.9) {
          entity->ChangeToDamaged();
        }

        if (entity->GetHealth() <= 0) {
          Pos position = entity->GetPos();
          // bool explodes = entity->Explodes();
          currentLevel->RemovePhysicalEntity(entity);

          if (entity->Explodes()) {
            currentLevel->AddExplosion(
                new Explosion(entity->GetPos().GetX() + 0.01f,
                              entity->GetPos().GetY() + 0.01f,
                              game.GetTexture("explosion1"),
                              game.GetTexture("explosion2"),
                              game.GetTexture("explosion3"), 0),
                500.0f);
          }
        }
      }
    }

    // std::cout << std::endl;
    // Update the window
    window.display();
  }

  return EXIT_SUCCESS;
}