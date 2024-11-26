#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include "level.hpp"
#include "background.hpp"

class Menu : Level {
    public:
        Menu(sf::Texture& texture);
        std::vector<Level*> GetLevels();
        Level* GetLevel(int i);

    private:
        std::vector<Level*> levels_; 
};

#endif