#ifndef MENU_HPP
#define MENU_HPP

#include "level.hpp"

class Menu : Level {
 public:
  Menu(std::map<std::string, sf::Texture>& textures,
       std::map<std::string, sf::SoundBuffer>& sfx, int width);
};

#endif