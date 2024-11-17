#include "fileManager.hpp"
#include "boxes.hpp"
#include <fstream>
#include <sstream>

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
std::vector<Box*> FileManager::LoadLevel(const std::string& filename){
    std::vector<Box*> boxes;
    std::ifstream file(filename);

    if(!file.is_open()){
        return boxes;
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
        if(type == "CONCRETE"){
            boxes.push_back(new Concrete(x,y));
        }
        else if(type == "WOOD"){
            boxes.push_back(new Wood(x,y));
        }
        else if(type == "GLASS"){
            boxes.push_back(new Glass(x,y));
        }
    }

    file.close();
    return boxes;
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
