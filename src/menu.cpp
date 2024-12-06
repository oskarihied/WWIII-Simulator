#include "menu.hpp"

#include "game.hpp"

Menu::Menu(Game& game) : GameView(game) {
  background_.setTexture(game_.GetTexture("menu"));
  background_.setScale(1.0f, 1.0f);

  AddNonPhysicalEntity(new Entity(4, 2.5, game.GetTexture("logo")));

  AddButton(
      new Button(7.7, 3.5, 0.5, 0.5, game.GetTexture("singleplayer_chosen")));
  AddButton(new Button(8.25, 3.5, 0.5, 0.5, game.GetTexture("multiplayer")));

  AddButton(new Button(2, 0, 1, 1, game.GetTexture("button1")));
  AddButton(new Button(4, 0, 1, 1, game.GetTexture("button2")));
  AddButton(new Button(6, 0, 1, 1, game.GetTexture("button3")));
}

void Menu::StepInTime(sf::RenderWindow& window) {
  sf::Event event;

  sf::Vector2i mousePos = sf::Mouse::getPosition(window);

  while (window.pollEvent(event)) {
    if (event.type == sf::Event::MouseButtonReleased) {
      Vector gamePos = game_.ToGamePos(mousePos.x, mousePos.y, *camera_);

      int index = 0;

      for (std::unique_ptr<Button>& button : buttons_) {
        if (button->IsTouching(gamePos.GetX(), gamePos.GetY())) {
          if (index == 0) {
            button->ChangeTexture(game_.GetTexture("singleplayer_chosen"));
            buttons_[1]->ChangeTexture(game_.GetTexture("multiplayer"));
            game_.SetMultiplayer(false);
          }

          else if (index == 1) {
            button->ChangeTexture(game_.GetTexture("multiplayer_chosen"));
            buttons_[0]->ChangeTexture(game_.GetTexture("singleplayer"));
            game_.SetMultiplayer(true);
          }

          else {
            game_.StartLevel(1);
            break;
          }
        }
        index++;
      }
    }
    if (event.key.scancode == sf::Keyboard::Scan::Escape) {
      window.close();
    }
  }
}

void Menu::Render(sf::RenderWindow& window) {
  window.draw(background_);

  for (std::unique_ptr<Entity>& entity : nonPhysicals_) {
    RenderEntity(entity, window);
  }

  for (std::unique_ptr<Button>& button : buttons_) {
    RenderEntity(button, window);
  }
}