#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include "level.hpp"

class Game {
    public:
        Game(int w, int h);

        Level startLevel();

        std::pair<int, int> ToScreenPos(Pos pos, Camera cam);

        std::vector<Entity> levelEntities() {
            return currentLevel_.GetEntities();
        }

    
    private:
        std::string playerName_;
        Level currentLevel_;

        int windowWidth_;
        int windowHeight_;
};
#endif
