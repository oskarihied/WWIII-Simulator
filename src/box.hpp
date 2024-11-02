#include "rigid.hpp"

class Box : public Rigid {
    public:
        Box(float x, float y);
        Box(float x, float y, float mass, int hp, int dur);

    protected:
        int durability_;
        std::vector<Rigid> contains_;
};