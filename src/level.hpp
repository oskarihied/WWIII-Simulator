#ifndef LEVEL_HPP
#define LEVEL_HPP

#include<vector>
#include "entity.hpp"
#include "camera.hpp"

class Level{
    public:
        Level();

        Camera GetCam();
        
        void AddEntity(Entity entity);

        std::vector<Entity> GetEntities();






    private:
        std::vector<Entity> entities_;
        Camera camera_;
        
};

#endif
