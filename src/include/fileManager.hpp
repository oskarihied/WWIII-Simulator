#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <string>
#include <vector>
#include <map>
#include "box.hpp"

class FileManager {
 public:

    bool SaveScore(const std::string& filename, std::vector<std::pair<std::string,int>> scores);
    std::vector<std::pair<std::string,int>> LoadScore(const std::string& filename);

    /*bool SaveLevel(const std::string& filename, const std::vector<Entity*>& entities);*/
    std::vector<Entity*> LoadLevel(const std::string& filename, std::map<std::string, sf::Texture>& textures);

    void LoadTextures(std::map<std::string, sf::Texture>& map, std::string path);

};

#endif