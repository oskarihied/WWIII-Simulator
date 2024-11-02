
#include <string>
#include "level.hpp"

class Game {
    public:
        Game(){};

        void startLevel();
    
    private:
        std::string playerName_;
        Level currentLevel_;
};