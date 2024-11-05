
#include <box2d/box2d.h>
#include "box.hpp"

class Physics {
    public:
        Physics();

        //simulate the simulation one simulation step
        void SimulateWorld(float simulationStep);

        bool AddBox(Box box); 


    private:
        b2World simulationWorld_;
        std::vector<Entity> entities_;
        std::vector<b2Body*> b2bodies_;
};