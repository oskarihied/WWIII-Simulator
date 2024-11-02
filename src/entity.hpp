
#include "pos.hpp"
#include <vector>
#include <string>

class Entity{
    public:
        Entity();
        Entity(float x, float y);

        Pos GetPos();
        void MoveTo(float x, float y);
        void MoveTo(Pos pos);

        std::pair<float, float> Move(float x, float y);
        std::pair<float, float> Move(Pos pos);

    protected:
        std::string sprite_;
        Pos pos_;
};