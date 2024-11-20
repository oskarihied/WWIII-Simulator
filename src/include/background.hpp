#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "nonPhysical.hpp"

class Background : NonPhysical {
    public:
        Background(sf::Texture& texture) : NonPhysical(0, 0, texture) {};
};

#endif