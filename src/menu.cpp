#include "menu.hpp"

#include "game.hpp"

Menu::Menu(Game& game) : GameView(game) {
  //Setup Background texture
  background_.setTexture(*FileManager::GetTexture("menu"));
  //Scale background
  background_.setScale(game.GetDimensions().GetX()/1599.0f, game.GetDimensions().GetY() * 1.3f /808.0f);

  //Create logo
  auto logo = std::make_unique<Entity>(4.0f, 2.5f);
  logo->SetTexture("logo");
  AddNonPhysicalEntity(std::move(logo));

  //create buttons
  auto singleplayer =
      std::make_unique<Button>(7.7f, 3.5f, 0.5f, 0.5f, "singleplayer_chosen");
  auto multiplayer =
      std::make_unique<Button>(8.25f, 3.5f, 0.5f, 0.5f, "multiplayer");

  auto level1 = std::make_unique<Button>(2.0f, 0.0f, 1.0f, 1.0f, "button1");
  auto level2 = std::make_unique<Button>(4.0f, 0.0f, 1.0f, 1.0f, "button2");
  auto level3 = std::make_unique<Button>(6.0f, 0.0f, 1.0f, 1.0f, "button3");

  //Add buttons to the menu
  AddButton(std::move(singleplayer));
  AddButton(std::move(multiplayer));

  AddButton(std::move(level1));
  AddButton(std::move(level2));
  AddButton(std::move(level3));
}

void Menu::StepInTime(sf::RenderWindow& window) {
  sf::Event event;

  sf::Vector2i mousePos = sf::Mouse::getPosition(window);
  Vector mouseVec = Vector(mousePos.x, mousePos.y);

  while (window.pollEvent(event)) {
    if (event.type == sf::Event::MouseButtonReleased) {
      Vector gamePos = game_.ToGamePos(mouseVec, *camera_);

      int index = 0;

      //Go through the buttons and check if they were pressed
      for (std::unique_ptr<Button>& button : buttons_) {
        if (button->IsTouching(gamePos.GetX(), gamePos.GetY())) {
          //singleplayer
          if (index == 0) {
            button->SetTexture("singleplayer_chosen");
            buttons_[1]->SetTexture("multiplayer");
            game_.SetMultiplayer(false);
          }
          //multiplayer
          else if (index == 1) {
            button->SetTexture("multiplayer_chosen");
            buttons_[0]->SetTexture("singleplayer");
            game_.SetMultiplayer(true);
          }
          //levels
          else {
            game_.StartLevel(index - 1);
            break;
          }
        }
        index++;
      }
    }
    //If esc is pressed, end game
    if (event.key.scancode == sf::Keyboard::Scan::Escape) {
      window.close();
    }
  }
}

void Menu::Render(sf::RenderWindow& window) {
  window.draw(background_);

  //render statics
  for (std::unique_ptr<Entity>& entity : nonPhysicals_) {
    RenderEntity(entity, window);
  }

  //render buttons
  for (std::unique_ptr<Button>& button : buttons_) {
    RenderEntity(button, window);
  }
}