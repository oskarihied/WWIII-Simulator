#ifndef LEVEL_HPP
#define LEVEL_HPP

#include<vector>
#include "entity.hpp"
#include "camera.hpp"
#include "physics.hpp"

class Level{
    public:
        Level();

        Camera* GetCam();
        
        void AddEntity(Entity* entity);
        void AddNonPhysicalEntity(Entity* entity);
        void AddBox(Box* box);

        Physics* GetPhysics();

        std::vector<Entity*> GetEntities();
        std::vector<Entity*> GetNonPhysicalEntities();



    private:
        Camera* camera_;
        Physics* physics_;
        const std::vector<Entity*>& entities_;
        std::vector<Entity*> nonPhysicals_;
        
};

#endif
