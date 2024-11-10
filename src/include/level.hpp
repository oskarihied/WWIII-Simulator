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
        void AddPhysicalEntity(Entity* entity);
        void AddBox(Box* box);

        Physics* GetPhysics();

        std::vector<Entity*> GetEntities();






    private:
        Camera* camera_;
        Physics* physics_;
        const std::vector<Entity*>& entities_;
        std::vector<std::pair<std::string,int>> leaderboard_;
        
        
};

#endif
