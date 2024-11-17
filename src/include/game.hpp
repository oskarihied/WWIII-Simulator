#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <map>
#include "level.hpp"
#include "fileManager.hpp"

class Game {
    public:
        Game(int w, int h);

        Level* startLevel();

        std::pair<int, int> ToScreenPos(Pos pos, Camera cam);

        std::vector<Entity*> levelEntities() {
            return currentLevel_->GetEntities();
        }

        void LoadTextures(FileManager& manager);

        sf::Texture& GetTexture(std::string name);

    
    private:
        std::string playerName_;
        Level* currentLevel_;

        int windowWidth_;
        int windowHeight_;

        std::map<std::string, sf::Texture> textures_;
};
#endif
