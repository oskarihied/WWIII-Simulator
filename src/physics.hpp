#ifndef PHYSICS_HPP
#define PHYSICS_HPP


#include <box2d/box2d.h>
#include "box.hpp"
#include "ground.hpp"

class Physics {
    public:
        Physics();

        //simulate the simulation one simulation step
        void SimulateWorld(float simulationStep);

        b2Body* AddBox(Box* box);
        b2Body* AddGround(Ground* ground);


        void SetVelocity(b2Body* body, float xVel, float yVel);
        void SetPosition(b2Body* body, float xPos, float yPos, float rotation);

        const std::vector<Entity*>& GetEntities() const {return entities_;}
        const std::vector<b2Body*>& GetBodies() const {return b2bodies_;}

    private:
        b2World simulationWorld_;
        std::vector<Entity*> entities_;
        std::vector<b2Body*> b2bodies_;
};

#endif