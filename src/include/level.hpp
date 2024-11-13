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
        void AddScore(std::string name, int score);
        void AddBoxes(std::vector<Box*> boxes);
        void AddScores(std::vector<std::pair<std::string,int>> scores);
        Physics* GetPhysics();

        std::vector<Entity*> GetEntities();

        std::vector<std::pair<std::string,int>> GetLeaderboard();



    private:
        Camera* camera_;
        Physics* physics_;
        const std::vector<Entity*>& entities_;
        std::vector<std::pair<std::string,int>> leaderboard_;
        
        
};

#endif
