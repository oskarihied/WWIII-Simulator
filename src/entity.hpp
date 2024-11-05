#ifndef ENTITY_HPP
#define ENTITY_HPP


#include "pos.hpp"
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

class Entity{
    public:
        Entity();
        Entity(float x, float y);
        Entity(float x, float y, std::string sprite);

        Pos GetPos();
        void MoveTo(float x, float y);
        void MoveTo(Pos pos);

        sf::Sprite &GetSprite();

        std::pair<float, float> Move(float x, float y);
        std::pair<float, float> Move(Pos pos);

    protected:
        std::string image_;
        Pos pos_;
        sf::Texture texture_;
        sf::Sprite sprite_;
        
};

#endif