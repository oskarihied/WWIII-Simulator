#include "menu.hpp"

Menu::Menu(std::map<std::string, sf::Texture>& textures,
           std::map<std::string, sf::SoundBuffer>& sfx)
    : Level(textures.at("menu"), sfx, true) {
  background_.setScale(0.9f, 0.9f);

  AddNonPhysicalEntity(new Entity(4, 2.5, textures.at("logo")));

  AddButton(new Button(7.7, 3.5, 0.5, 0.5, textures.at("singleplayer_chosen")));
  AddButton(new Button(8.25, 3.5, 0.5, 0.5, textures.at("multiplayer")));

  AddButton(new Button(2, 0, 1, 1, textures.at("button1")));
  AddButton(new Button(4, 0, 1, 1, textures.at("button2")));
  AddButton(new Button(6, 0, 1, 1, textures.at("button3")));
}