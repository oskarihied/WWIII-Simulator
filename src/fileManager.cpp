#include "fileManager.hpp"
#include "boxes.hpp"
#include "enemy.hpp"
#include <fstream>
#include <sstream>
#include <filesystem>

bool FileManager::SaveScore(const std::string& filename, std::vector<std::pair<std::string,int>> scores){
    std::ofstream file(filename);

    if (!file.is_open()){
        return false;
    }

    for(auto it : scores){
        file << it.first << ";" << it.second << "\n";
    }

    file.close();
    return true;
}

std::vector<std::pair<std::string,int>> FileManager::LoadScore(const std::string& filename){
    std::vector<std::pair<std::string,int>> scores;
    std::ifstream file(filename);

    if(!file.is_open()){
        return scores;
    }

    std::string line;
    while(std::getline(file, line)){
        std::istringstream stream(line);
        std::string name;
        int score;
        std::getline(stream,name,';');
        stream >> score;
        scores.push_back(std::make_pair(name,score));
    }

    file.close();
    return scores;
}

/*bool FileManager::SaveLevel(const std::string& filename, const std::vector<Entity*>& entities){
    std::ofstream file(filename);

    if(!file.is_open()){
        return false;
    }

    for(auto it : entities){
        file << it->GetPos
    }
}*/
std::vector<Entity*> FileManager::LoadLevel(const std::string& filename, std::map<std::string, sf::Texture>& textures){
    std::vector<Entity*> entities;
    std::ifstream file(filename);

    if(!file.is_open()){
        return entities;
    }

    std::string line;
    while(std::getline(file, line)){
        std::istringstream stream(line);
        std::string type;
        int x, y;
        std::getline(stream,type,';');
        stream >> x;
        stream.ignore();
        stream >> y;
        if(type == "C"){
            entities.push_back(new Concrete(x,y,textures.at("concrete")));
        }
        else if(type == "W"){
            entities.push_back(new Wood(x,y,textures.at("wood")));
        }
        else if(type == "G"){
            entities.push_back(new Glass(x,y,textures.at("glass")));
        }
        else if(type == "E"){
            entities.push_back(new Enemy(x,y,textures.at("enemy")));
        }
    }

    file.close();
    return entities;
}

void FileManager::LoadTextures(std::map<std::string, sf::Texture>& map, std::string path) {

    map.clear();

    int i = 0;

    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        sf::Texture thisTexture;
        thisTexture.loadFromFile(entry.path());

        std::string name = entry.path();
        name.erase(0, (int)(path.length() + 1));
        name.erase(name.length() - 4);

        map.insert({name, thisTexture});

        //std::cout << name  << " " << i << std::endl;

        i++;
    }
}
