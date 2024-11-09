#ifndef RIGID_HPP
#define RIGID_HPP

#include "physical.hpp"

class Rigid : public Physical {
    public:
        Rigid(float x, float y);
        Rigid(float x, float y, float mass, int hp);
    
    protected:
        int maxHP_;
        int currentHP_;
};

#endif