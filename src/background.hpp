#include "nonPhysical.hpp"

class Background : NonPhysical {
    public:
        Background(std::string image) : NonPhysical(0, 0, image) {};
};