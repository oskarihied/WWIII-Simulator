
#include "entity.hpp"

class NonPhysical : public Entity {
    public:
        NonPhysical(float x, float y);
        NonPhysical(float x, float y, std::string image);
        NonPhysical(float x, float y, sf::Texture& texture);
};