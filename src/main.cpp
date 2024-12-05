#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>

#include "game.hpp"
#include "physics.hpp"

int main() {
  // Create the main window

  std::cout << "Current working directory: " << std::filesystem::current_path()
            << std::endl;

  int w = 1300;
  int h = 700;

  Game game = Game(w, h);
  sf::Clock timer;

  game.StartMenu();

  Level* currentLevel = game.GetCurrentLevel();

  Bullet* currentBullet = nullptr;

  sf::RenderWindow window(sf::VideoMode(w, h), "WWIII Simulator",
                          sf::Style::Fullscreen);

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
      currentLevel->GetPhysics()->SimulateWorld(1.0f / 60.0f);

      Gun* gun = currentLevel->CurrentGun();

      if (currentLevel->GetTimer() > 0 && currentLevel->GetTimer() <= 2 &&
          !currentBullet->IsDead()) {
        currentLevel->GetCam()->MoveTo(currentBullet->GetPos().GetX() - 5,
                                       currentLevel->GetCam()->GetPos().GetY());
      }

      if (gun) {
        currentLevel->AddBulletTimer(1.0f / 60.0f);

        if (currentLevel->GetTimer() > 2) {
          // currentLevel->GetCam()->MoveTo(currentBullet->GetPos().GetX() - 5,
          // currentLevel->GetCam()->GetPos().GetY());
          currentLevel->SetTimer(false);

          if (gun->GetPos().GetX() == 0) {
            currentLevel->GetCam()->NewAnimation(
                Pos(gun->GetPos().GetX() - 5, 7), 15, 2);
          }

          else {
            currentLevel->GetCam()->NewAnimation(
                Pos(gun->GetPos().GetX() - 10, 7), 15, 2);
          }
        }

        currentLevel->GetCam()->AnimationStep(1.0f / 60.0f);
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

          int index = 0;

          for (Button* button : currentLevel->GetButtons()) {
            if (button->IsTouching(gamePos.GetX(), gamePos.GetY())) {
              if (index == 0) {
                button->GetEntity()->ChangeTexture(
                    game.GetTexture("singleplayer_chosen"));
                currentLevel->GetButtons()[1]->GetEntity()->ChangeTexture(
                    game.GetTexture("multiplayer"));
                game.SetMultiplayer(false);
              }

              else if (index == 1) {
                button->GetEntity()->ChangeTexture(
                    game.GetTexture("multiplayer_chosen"));
                currentLevel->GetButtons()[0]->GetEntity()->ChangeTexture(
                    game.GetTexture("singleplayer"));
                game.SetMultiplayer(true);
              }

              else {
                game.StartLevel(1);
                currentLevel = game.GetCurrentLevel();
              }
            }

            index++;
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
            game.StartMenu();
            currentLevel = game.GetCurrentLevel();
          }
        }

        if (event.type == sf::Event::MouseButtonPressed) {
          timer.restart();
        }

        if (event.type == sf::Event::MouseButtonReleased) {
          float vel = std::min(timer.getElapsedTime().asSeconds(), 2.0f);
          currentBullet = currentLevel->CurrentGun()->GetBullet();
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
    std::vector<sf::Sound*> currentSounds;
    for (auto sound : currentLevel->GetSounds()) {
      if (sound->getStatus() != sf::Sound::Status::Playing) {
        delete sound;
      } else {
        currentSounds.push_back(sound);
      }
    }
    currentLevel->GetSounds() = currentSounds;

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
      for (Entity* entity : currentLevel->GetPhysics()->GetEntities()) {
        // std::cout << entity->GetSprite() << std::endl;

        float scale = (w / 200.0f) / currentLevel->GetCam()->GetZoom();

        entity->GetSprite()->setScale(sf::Vector2(scale, scale));
        entity->GetSprite()->setRotation(-entity->GetRotation());

        std::pair<int, int> pos =
            game.ToScreenPos(entity->GetPos(), *currentLevel->GetCam());

        // std::cout << entity->GetHealth() << std::endl;

        entity->GetSprite()->setPosition(pos.first, -pos.second);

        window.draw(*(entity->GetSprite()));

        if (!entity->IsDead()) {
          if (entity->GetHealth() <= entity->GetMaxHealth() * 0.9) {
            entity->ChangeToDamaged();
          }

          if (entity->GetHealth() <= 0) {
            entity->Die();
            currentLevel->AddPoints(entity->GetPoints());

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
              currentLevel->PlaySound("explosion");
            }
          }
        }
      }

      int n = 0;
      int i = 0;
      for (Gun* gun : currentLevel->GetGuns()) {
        if (game.GetMultiplayer() && n % 2 == 0) {
          gun->GetSprite()->setScale(sf::Vector2(0.5f, 0.5f));
          gun->GetSprite()->setPosition(50, 20 + i * 40);
          window.draw(*(gun->GetSprite()));
          i++;
        }
        n++;
      }
    }

    // std::cout << currentLevel->GetPoints() <<std::endl;
    //  Update the window

    window.display();
  }

  return EXIT_SUCCESS;
}