#ifndef MENU_HPP
#define MENU_HPP

#include "background.hpp"
#include "level.hpp"

class Menu : Level {
 public:
  Menu(std::map<std::string, sf::Texture>& textures);
};

#endif