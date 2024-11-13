#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>

#include "bullets.hpp"
#include "camera.hpp"
#include "entity.hpp"
#include "physics.hpp"

class Level {
 public:
        Level();

        Camera* GetCam();
        
        void AddEntity(Entity* entity);
        void AddNonPhysicalEntity(Entity* entity);
        void AddBox(Box* box);
        void AddScore(std::string name, int score);
        void AddBoxes(std::vector<Box*> boxes);
        void AddScores(std::vector<std::pair<std::string,int>> scores);
        Physics* GetPhysics();
        void Fire();


        std::vector<Entity*> GetEntities();
        std::vector<Entity*> GetNonPhysicalEntities();

        std::vector<std::pair<std::string,int>> GetLeaderboard();
        Entity* CurrentGun();
        //std::vector<Entity*> GetGuns();
        void AddGun(Entity* gun);



    private:
        Camera* camera_;
        Physics* physics_;
        std::vector<Bullet*> bullets_;
        const std::vector<Entity*>& entities_;
        std::vector<std::pair<std::string,int>> leaderboard_;
        std::vector<Entity*> nonPhysicals_;
        std::vector<int> guns_;
        
};

#endif
