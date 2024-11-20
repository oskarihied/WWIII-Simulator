#include "menu.hpp"

Menu::Menu(sf::Texture& texture) 
    : Level(texture) {
        background_.setScale(0.9f, 0.9f);
    }

std::vector<Level*> Menu::GetLevels() {
    return levels_;
}

Level* Menu::GetLevel(int i) {
    return levels_[i];
}