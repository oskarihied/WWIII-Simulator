#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "pos.hpp"
#include "entity.hpp"

class Button {
    public:
        Button(float x, float y, float sizeX, float sizeY, sf::Texture& texture);
        
        Entity* GetEntity();
        bool IsTouching(float x, float y);

    private:
        Pos pos_;
        float sizeX_;
        float sizeY_;
        Entity* entity_;
        
};

#endif