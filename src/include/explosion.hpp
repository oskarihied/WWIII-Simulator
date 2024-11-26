#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include "entity.hpp"

class Explosion : public Entity {
    public:
        Explosion(float x, float y, sf::Texture& texture1, sf::Texture& texture2, sf::Texture& texture3, int count);

        int GetCount();
        void NextSprite();

    private:
        int count_;
        sf::Texture& texture1_;
        sf::Texture& texture2_;
        sf::Texture& texture3_;
};

#endif